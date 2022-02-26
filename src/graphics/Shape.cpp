#include "Shape.h"

namespace psgui::graphics {
	Shape::Shape() {
		this->init();
	}
	Shape::Shape(float x, float y): Shape(Vector2{x,y}) {}
	Shape::Shape(float x, float y, float width, float height): Shape(Vector2{x,y},Vector2{width,height}) {}
	Shape::Shape(Vector2 position): position(position), size(Vector2{0,0}) {
		this->init();
	}
	Shape::Shape(Vector2 position, Vector2 size): position(position), size(size) {
		this->init();
	}
	Shape::~Shape() {}

	void Shape::init() {
		TraceLog(LOG_DEBUG, "initting shape");
		this->draw_outline = false;
		this->rotation = 0.f;
		this->origin = {0.f,0.f};
	}

	void Shape::setPosition(Vector2 position) {
		this->position = position;
	}

	void Shape::setPosition(float x, float y) {
		this->setPosition(Vector2{x,y});
	}

	void Shape::setSize(Vector2 size) {
		this->size = size;
	}

	void Shape::setSize(float x, float y) {
		this->setSize(Vector2{x,y});
	}

	void Shape::setWidth(float w) {
		this->size.x = w;
	}

	void Shape::setHeight(float h) {
		this->size.y = h;
	}

	void Shape::setFillColor(Color color) {
		this->fill_color = color;
	}

	void Shape::setOutlineColor(Color color) {
		this->outline_color = color;
	}

	void Shape::setOutlineThickness(float thickness) {
		this->outline_thickness = thickness;
	}

	void Shape::setOutline(bool state) {
		this->draw_outline = state;
	}

	void Shape::toggleOutline() {
		this->draw_outline = !this->draw_outline;
	}

	void Shape::setRotation(float rotation) {
		this->rotation = rotation;
	}
}
