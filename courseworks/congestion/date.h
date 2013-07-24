#ifndef DATE_H
#define DATE_H
class Date {
  friend class DateTest;
  friend std::ostream& operator<<(std::ostream& out, const Date& date);
  friend bool operator==(const Date& date1, const Date& date2);
  friend bool operator!=(const Date& date1, const Date& date2);

 public:
  Date(int d, int m, int y);

 private:
  int day, month, year;
  
};
#endif
