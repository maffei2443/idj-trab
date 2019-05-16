#ifndef TIMER_H
#define TIMER_H
class Timer {
private:
  double time = 0.0;
public:
  void Update(double dt);
  void Restart(void);
  double Get() const;
  // Timer();
};
#endif