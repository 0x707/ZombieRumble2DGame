#include "Score.h"
#include <fstream>
#include <cassert>

namespace game {

	void Score::update_high_score()
	{
		if (score_ > high_score_)
			high_score_ = score_;
	}

	int Score::load_high_score()
	{
		std::ifstream ifs{ "score.txt" };
		if (ifs.is_open()) {
			ifs >> high_score_;
			ifs.close();
			return high_score_;
		}
		assert(false);
		return -1;
	}

	void Score::save_high_score() const
	{
		std::ofstream ofs{ "score.txt" };
		ofs << high_score_ << '\n';
		ofs.close();
	}

} // namespace game