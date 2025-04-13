#include "PToolbar.h"

void PToolbar::Draw(Screen& screen)
{

	const Rect rect = Rect(pos, size);
	const SDL_Color color = { 169,169,169,255 };

	screen.GetRenderer().DrawRect(rect, color);
	backBtn.Draw(screen);
	resetBtn.Draw(screen);
}

void PToolbar::load(Screen& screen, TTF_Font* font)
{
	const auto size = screen.GetWindow().GetSize();
	pos.x = 0; pos.y = 0; this->size.w = size.w; this->size.h = 32;
	backBtn = TextButton("Back", screen.GetRenderer(), Point(10, 0), font);
	auto x = backBtn.GetPosition().x + backBtn.rectSize.w + 10;
	resetBtn = TextButton("Reset", screen.GetRenderer(), Point(x, 0), font);
}

Rect PToolbar::GetRect() const
{
	return Rect(pos, size);
}