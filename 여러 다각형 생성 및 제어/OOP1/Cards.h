#pragma once
#include "GameObject.h"
#include "Card.h"
#include <vector>

using namespace std;

enum class CardsState {
	Idle,
	Detecting,
	Waiting,
	Removing,
	Assigning
};


class Cards :
    public GameObject
{
	int n_cols;
	int n_rows;
	Dimension cardDim;
	Card* source;
	Card* destination;

	vector<int> cardTypes;
	vector<GameObject*> cards;

	int n_frames_waiting;

	vector<int> continuousList;
	
	CardsState state;

	vector<int> findContinuity(int startingCellNo, int direction) const
	{
		// startingCellNo is assumed to be \in [ 0, n_cols * n_rows )
		vector<int> results;
		int type = cardTypes[startingCellNo];
		if (type == 0) return results;

		results.push_back(startingCellNo);
		auto mePos = no2pos(startingCellNo);
		auto inc = direction == 1 ? 1 : n_cols;
		for (int next = startingCellNo + inc; 
			next < startingCellNo + (direction == 1 ? 1 : n_rows ) * n_cols; 
			next += inc )
		{
			if (next < 0 || next >= n_cols * n_rows) break;
			auto nextPos = no2pos(next);
			if (direction == 1 && nextPos.y != mePos.y) break; // examine horizontally continuous types
			if (direction != 1 && nextPos.x != mePos.x) break; // examine vertically continuous types
			if (type != cardTypes[next]) return results;
			results.push_back(next);
		}
		return results;
	}

	int randomizeType() const { return  rand() % 3 + 1; }

public:
	Cards(int n_cols, int n_rows, const Dimension& dim) : 
		GameObject("", Vector2{ 0, 0 }, { 0, 0 }, false), 
		source(nullptr), destination(nullptr), 
		n_cols(n_cols), n_rows(n_rows), cardDim(dim),
		n_frames_waiting(0), 
		state(CardsState::Detecting),
		continuousList(0)
	{	
		for (int i = 0; i < n_rows* n_cols; i++)
		{
			auto type = randomizeType();
			cardTypes.push_back(type);
			auto card = new Card(*this, type, no2pos(i), dim, true);
			cards.push_back(card);
			GameObject::Add(card);
		}
	}

	~Cards() {
		while (cards.size()) {
			auto obj = cards.back();
			GameObject::Remove(obj);
			cards.pop_back();
		}
		cardTypes.clear();
	}

	Card* getSource() const { return source; }
	Card* getDestination() const { return destination; }
	void setSource(Card* card) { source = card; }
	void setDestination(Card* card) { destination = card; }

	int pos2no(const Position& pos) const { return (pos.x / cardDim.x) % n_cols + (pos.y / cardDim.y) * n_cols; }
	int pos2no(const Vector2& pos) const { return pos2no(Position{ (int)pos.x, (int)pos.y }); }

	Position no2pos(int no) const { return Position{ (no % n_cols) * cardDim.x, (no / n_cols) * cardDim.y }; }

	void swap() {
		if (source == nullptr || destination == nullptr) return;

		auto s_no = source->getNo();
		auto d_no = destination->getNo();

		Debug::Log("swap [%d] <-> [%d]", s_no, d_no);
		
		cardTypes[s_no] = destination->getType();
		cardTypes[d_no] = source->getType();
		cards[s_no] = destination;
		destination->setNo(s_no);
		cards[d_no] = source;
		source->setNo(d_no);

		state = CardsState::Detecting;
		source = nullptr;
		destination = nullptr;
	}

	void update(InputManager& input) override;
};

