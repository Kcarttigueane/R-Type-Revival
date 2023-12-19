#ifndef ECS_SCORE_COMPONENT_HPP
#define ECS_SCORE_COMPONENT_HPP

struct ScoreComponent {
  int score;
  float multiplier; // Score multiplier for combos or special actions
  int bonusPoints;  // Bonus points earned through specific actions
};

#endif // ECS_SCORE_COMPONENT_HPP
