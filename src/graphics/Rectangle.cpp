#include "Rectangle.h"

namespace psgui::graphics {
	Rectangle::Rectangle(): Shape() {
		this->init();
	}
	Rectangle::Rectangle(float x, float y): Rectangle(Vector2{x, y}) {}
	Rectangle::Rectangle(float x, float y, float width, float height): Rectangle(Vector2{x, y}, Vector2{width, height}) {}
	Rectangle::Rectangle(Vector2 position): Shape(position) {
		this->init();
	}
	Rectangle::Rectangle(Vector2 position, Vector2 size): Shape(position, size) {
		this->init();
	}
	Rectangle::~Rectangle() {}

	void Rectangle::init() {
		// Shape::init(); // shape constructor already does its own init
		TraceLog(LOG_DEBUG, "initting rect");
		this->rect.x = this->position.x;
		this->rect.y = this->position.y;
		this->rect.width = this->size.x;
		this->rect.height = this->size.y;
	}

	void Rectangle::setPosition(Vector2 position) {
		this->setPosition(position.x, position.y);
	}

	void Rectangle::setPosition(float x, float y) {
		this->rect.x = x;
		this->rect.y = y;
	}

	void Rectangle::setSize(Vector2 size) {
		this->setSize(size.x, size.y);
	}

	void Rectangle::setSize(float x, float y) {
		this->rect.width = x;
		this->rect.height = y;
	}

	void Rectangle::setWidth(float w) {
		this->rect.width = w;
	}

	void Rectangle::setHeight(float h) {
		this->rect.height= h;
	}

	void Rectangle::render() const {
		DrawRectanglePro(this->rect, this->origin, this->rotation, this->fill_color);
		if(this->draw_outline) {
			DrawRectangleLinesEx(this->rect, this->outline_thickness, this->outline_color);
		}
	}
}
