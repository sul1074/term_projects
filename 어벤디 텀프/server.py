from flask import Flask, render_template, Response, request, jsonify
import cv2
import serial
import logging
import time
from threading import Thread, Lock

# Flask 앱 초기화
app = Flask(__name__)
logging.basicConfig(level=logging.DEBUG, format='%(asctime)s - %(levelname)s - %(message)s')

# 카메라 초기화
camera = cv2.VideoCapture(0)  # 기본 카메라 사용
camera.set(cv2.CAP_PROP_FRAME_WIDTH, 640)  # 해상도 설정
camera.set(cv2.CAP_PROP_FRAME_HEIGHT, 480)

if not camera.isOpened():
    logging.error("카메라를 열 수 없습니다. 장치가 연결되었는지 확인하세요.")
    exit()

# 아두이노와 시리얼 통신 설정
arduino_lock = Lock()
try:
    arduino = serial.Serial('/dev/serial0', 9600)  # UART 포트 연결
    time.sleep(5)  # 아두이노 초기화 대기
except Exception as e:
    logging.error(f"아두이노 연결 실패: {e}")
    arduino = None

# 프레임 생성기
frame_lock = Lock()
def generate_frames():
    while True:
        with frame_lock:
            success, frame = camera.read()
            if not success:
                logging.error("카메라 프레임을 읽을 수 없습니다.")
                break
            _, jpeg = cv2.imencode('.jpg', frame)
            frame_bytes = jpeg.tobytes()
            yield (b'--frame\r\n'
                   b'Content-Type: image/jpeg\r\n\r\n' + frame_bytes + b'\r\n')

@app.route('/video_feed')
def video_feed():
    return Response(generate_frames(), mimetype='multipart/x-mixed-replace; boundary=frame')

# 명령어 처리 스레드
last_command = None

@app.route('/command', methods=['POST'])
def send_command():
    global last_command
    data = request.get_json()
    command = data.get('command', '')

    if not command:
        return jsonify({'status': 'error', 'message': 'No command provided'}), 400

    try:
        with arduino_lock:
            if arduino:
                # 명령 전송 사이에 지연 추가
                if command != last_command or command in ['x', 't']:  # LED, 펌프 명령은 중복 전송 허용
                    arduino.write(command.encode())
                    time.sleep(0.1)  # 짧은 지연 추가
                    last_command = command
                return jsonify({'status': 'success', 'message': f'Command {command} sent to Arduino'}), 200
            else:
                return jsonify({'status': 'error', 'message': 'Arduino not connected'}), 500
    except Exception as e:
        logging.error(f"명령 처리 중 오류 발생: {e}")
        return jsonify({'status': 'error', 'message': str(e)}), 500

@app.route('/')
def index():
    return render_template('index.html')

# 카메라 스트리밍 스레드 관리
streaming_thread = Thread(target=generate_frames, daemon=True)
streaming_thread.start()

@app.route('/shutdown', methods=['POST'])
def shutdown_streaming():
    try:
        logging.info("Shutting down camera stream...")
        with frame_lock:
            camera.release()
        return "Streaming stopped.", 200
    except Exception as e:
        logging.error(f"Failed to stop camera streaming: {e}")
        return "Error stopping streaming", 500

# 서버 실행
if __name__ == "__main__":
    try:
        app.run(host="0.0.0.0", port=5005, threaded=True)
    finally:
        # 서버 종료 시 리소스 해제
        if camera.isOpened():
            camera.release()
        if arduino:
            arduino.close()