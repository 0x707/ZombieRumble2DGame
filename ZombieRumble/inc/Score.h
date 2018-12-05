#ifndef SCORE_CLASS_H_
#define SCORE_CLASS_H_

namespace game {

	class Score
	{
	public:
		Score(Score const&) = delete;
		Score& operator=(Score const&) = delete;

		static Score& get_instance()
		{
			static Score score;
			return score;
		}

		int& operator+=(int value) { return score_ += value; }
		int operator+(int value) const { return score_ + value; }

		int get_score() const { return score_; }
		int get_hscore() const { return high_score_; }
		void reset_score() { score_ = 0; }
		void update_high_score();
		int load_high_score();
		void save_high_score() const;
	private:
		int score_ = 0;
		int high_score_ = 0;

		Score() {}
	};

} // namespace game

#endif // !SCORE_CLASS_H_
