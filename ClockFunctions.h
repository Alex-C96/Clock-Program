using namespace std;
void DisplayClock(int user12Hour, int user12Min, int user12Second, string amPm, int user24Hour, int user24Min, int user24Sec);
void ClockLoop();
void AddHour(int& hours_12, int& hours_24, string& meridian);
string StringConverter(int hour, int minute, int second, string meridian = "none");
int TimeConverter(int userHr);

