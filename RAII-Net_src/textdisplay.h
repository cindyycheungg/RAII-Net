#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <string>
#include <vector>

using namespace std;

class TextDisplay
{
	public:
	void notify(int x, int y, string symbol);
	TextDisplay();
	~TextDisplay();
	friend ostream &operator<<(ostream &out, const TextDisplay &td);
	private:
	vector<vector<string>> display;

};


#endif
