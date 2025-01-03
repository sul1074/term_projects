#include <algorithm>
#include "Cards.h"
#include "Card.h"

void Cards::update(InputManager& input)
{
	switch (state) {
	case CardsState::Idle:
		break;
	case CardsState::Detecting:
		continuousList.clear();
		for (auto i = 0; i < n_cols * n_rows; i++) {
			auto l1 = findContinuity(i, 1); // examine rows 
			auto l2 = findContinuity(i, 2); // examine columns
			if (l1.size() >= 3)	continuousList.insert(continuousList.end(), l1.begin(), l1.end());
			if (l2.size() >= 3) continuousList.insert(continuousList.end(), l2.begin(), l2.end());
			if (continuousList.size() >= 3) break;
		}
		if (continuousList.size() >= 3) {
			for (auto cellNo : continuousList)
				static_cast<Card*>(cards[cellNo])->setBlinkingPeriod(20);
			n_frames_waiting = 20;
			state = CardsState::Waiting;
		}
		else {
			state = CardsState::Idle;
		}
		break;
	case CardsState::Waiting:
		if (n_frames_waiting > 0) {
			n_frames_waiting--;
			if (n_frames_waiting == 0) 
				state = CardsState::Removing;
		}
		break;
	case CardsState::Removing:
		for_each(continuousList.begin(), continuousList.end(),
			[&](auto no) {
				cardTypes[no] = 0;
				static_cast<Card*>(cards[no])->setType(cardTypes[no]);
			}
		);
		
		n_frames_waiting = 20;
		state = CardsState::Assigning;
		break;
	case CardsState::Assigning:
		if (n_frames_waiting == 0) {
			for_each(continuousList.begin(), continuousList.end(),
				[&](auto no) {
					cardTypes[no] = randomizeType();
					static_cast<Card*>(cards[no])->setType(cardTypes[no]);
				}
			);
			state = CardsState::Detecting;
			break;
		}
		n_frames_waiting--;
		break;
	}
}