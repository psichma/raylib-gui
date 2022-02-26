#pragma once
#include "Shape.h"

// to avoid overhead this class does not use the position and size member from Shape
namespace psgui::graphics {
	class Rectangle: public Shape {
		protected:
			::Rectangle rect;
			virtual void init();
		public:
			Rectangle();
			Rectangle(float x, float y);
			Rectangle(float x, float y, float width, float height);
			Rectangle(Vector2 position);
			Rectangle(Vector2 position, Vector2 size);
			virtual ~Rectangle();

			virtual void setPosition(float x, float y);
			virtual void setPosition(Vector2 position);
			virtual Vector2 getPosition() const {return {this->rect.x, this->rect.y};}

			virtual void setSize(Vector2 size);
			virtual void setSize(float x, float y);
			virtual Vector2 getSize() const {return {this->rect.width, this->rect.height};}

			virtual void setWidth(float w);
			virtual float getWidth() const {return this->rect.width;}
			virtual void setHeight(float h);
			virtual float getHeight() const {return this->rect.height;}

			virtual void update(float delta) {}
			virtual void render() const;

	};
}
