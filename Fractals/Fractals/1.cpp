#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

double len = 400;

struct node {
	RectangleShape line;
	double x;
	double y;
	double xv, yv;
	int orientation;
	double angle;
	node(RectangleShape line, double x, double y) : line(line), x(x), y(y), xv(0), yv(400), orientation(1), angle(0) {}
};

double count_len(double x, double y) {
	return sqrt(x * x - y * y);
}

const double PI = 3.1415926535;
vector<vector<node> > stack;

void gen(vector<node>& lines) {
	len /= 3.0;
	int n = lines.size();
	vector<node> lines0;
	for (int i = 0; i < n; i++) {
		auto line1 = lines[i];
		line1.line.setSize(Vector2f(1, len));
		line1.xv /= 3.0;
		line1.yv /= 3.0;
		line1.line.setPosition(line1.x + line1.xv, line1.y + line1.yv);
		line1.x += line1.xv;
		line1.y += line1.yv;
		line1.line.rotate(-60);
		double rad = -60.0 / 180.0 * PI;
		double x0 = line1.xv * cos(rad) - line1.yv * sin(rad);
		double y0 = line1.xv * sin(rad) + line1.yv * cos(rad);
		line1.xv = x0;
		line1.yv = y0;

		auto line2 = lines[i];
		line2.line.setSize(Vector2f(1, len));
		line2.xv /= 3.0;
		line2.yv /= 3.0;
		line2.line.setPosition(line2.x + 2.0 * line2.xv, line2.y + 2.0 * line2.yv);
		line2.x += 2.0 * line2.xv;
		line2.y += 2.0 * line2.yv;
		line2.line.rotate(60.0);
		rad = 60.0 / 180.0 * PI;
		x0 = line2.xv * cos(rad) - line2.yv * sin(rad);
		y0 = line2.xv * sin(rad) + line2.yv * cos(rad);
		line2.xv = x0;
		line2.yv = y0;
		line2.line.setPosition(line2.x - line2.xv, line2.y - line2.yv);
		line2.x -= line2.xv;
		line2.y -= line2.yv;

		auto line3 = lines[i];
		line3.line.setSize(Vector2f(1, len));
		line3.xv /= 3.0;
		line3.yv /= 3.0;
		line3.line.setPosition(line3.x + 2.0 * line3.xv, line3.y + 2.0 * line3.yv);
		line3.x += 2.0 * line3.xv;
		line3.y += 2.0 * line3.yv;

		auto line4 = lines[i];
		line4.line.setSize(Vector2f(1, len));
		line4.xv /= 3.0;
		line4.yv /= 3.0;
		
		lines0.push_back(line1);
		lines0.push_back(line2);
		lines0.push_back(line3);
		lines0.push_back(line4);
	}
	lines = lines0;
	return;
}

int main() {
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Koch snowflake", Style::Fullscreen);
	RectangleShape background(Vector2f(2000, 2000));
	background.setFillColor(Color(19, 19, 89));
	background.setPosition(0, 0);

	RectangleShape line10(Vector2f(1, 400));
	line10.setPosition(1100, 350);
	auto line1 = node(line10, 1100, 350);

	auto line2 = line1;
	line2.line.rotate(-120);
	double rad = -120 / 180.0 * PI;
	double x0 = line2.xv * cos(rad) - line2.yv * sin(rad);
	double y0 = line2.xv * sin(rad) + line2.yv * cos(rad);
	line2.xv = x0;
	line2.yv = y0;
	line2.line.setPosition(line2.x - line2.xv, line2.y - line2.yv);
	line2.x -= line2.xv;
	line2.y -= line2.yv;

	auto line3 = line1;
	line3.line.rotate(120);
	rad = 120 / 180.0 * PI;
	x0 = line3.xv * cos(rad) - line3.yv * sin(rad);
	y0 = line3.xv * sin(rad) + line3.yv * cos(rad);
	line3.xv = x0;
	line3.yv = y0;
	line3.line.setPosition(line3.x, line3.y + 400);
	line3.y += 400;

	vector<node> lines;
	lines.push_back(line1);
	lines.push_back(line2);
	lines.push_back(line3);
	stack.push_back(lines);

	int cnt = 0;
	int ITSTIME = 700;
	int cnt2 = ITSTIME;
	int level = 1;
	while (window.isOpen()) {
		Event key;
		while (window.pollEvent(key)) {
			if (Keyboard::isKeyPressed(Keyboard::Escape)) {
				window.close();
			}
			else if (level < 8 && cnt == 100 && Keyboard::isKeyPressed(Keyboard::Space)) {
				gen(lines);
				stack.push_back(lines);
				cnt = 0;
				level++;
				ITSTIME -= 100;
			}
			else if (Keyboard::isKeyPressed(Keyboard::F5)) {
				lines.clear();
				lines.push_back(line1);
				lines.push_back(line2);
				lines.push_back(line3);
				stack.clear();
				stack.push_back(lines);
				ITSTIME = 700;
				len = 400;
				level = 1;
			}
			else if (cnt == 100 && Keyboard::isKeyPressed(Keyboard::BackSpace) && stack.size() > 1) {
				cnt = 0;
				level--;
				stack.pop_back();
				lines = stack.back();
				ITSTIME += 100;
				len *= 3.0;
			}
		}

		window.clear();
		window.draw(background);

		if (cnt2 == ITSTIME) {
			for (int i = 0; i < lines.size(); i++) {
				lines[i].line.setFillColor(Color(rand(), rand(), rand()));
			}
			cnt2 = 0;
		}

		for (int i = 0; i < lines.size(); i++) {
			window.draw(lines[i].line);
		}
		window.display();
		cnt = min(cnt + 1, 100);
		cnt2 = min(cnt2 + 1, ITSTIME);
	}

	return 0;
}