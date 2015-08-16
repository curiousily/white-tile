#ifndef RESOURCEFINDER_H_
#define RESOURCEFINDER_H_

#include "cocos2d.h"
#include "VisibleRect.h"
#include "SoundManager.h"
#include "Constants.h"
#include <string>

USING_NS_CC;

class LabelBuilder: Ref {
public:
	static LabelBuilder* label(const char* text, const char* font) {
		auto builder = new LabelBuilder();
		builder->init(text, font);
		builder->autorelease();
		return builder;
	}

	static LabelBuilder* label(const char* text) {
		auto builder = new LabelBuilder();
		builder->initWithGlobalFont(text);
		builder->autorelease();
		return builder;
	}

	LabelBuilder* size(int fontSize) {
		aLabel->setSystemFontSize(fontSize);
		return this;
	}

	LabelBuilder* position(Point position) {
		aLabel->setPosition(position);
		return this;
	}

	LabelBuilder* anchorPoint(Point anchorPoint) {
		aLabel->setAnchorPoint(anchorPoint);
		return this;
	}

	LabelBuilder* color(Color3B color) {
		aLabel->setColor(color);
		return this;
	}

	LabelBuilder* opacity(int opacity) {
		aLabel->setOpacity(opacity);
		return this;
	}

	LabelBuilder* dimensions(const Size& dimensions) {
		aLabel->setDimensions(dimensions.width, dimensions.height);
		return this;
	}

	Label* addTo(Node* node) {
		node->addChild(aLabel);
		return getLabel();
	}

	Label* getLabel() {
		return aLabel;
	}

private:

	void init(const char* text, const char* font) {

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        aLabel = Label::createWithSystemFont(text, font, DEFAULT_FONT_SIZE);
#else

		aLabel = Label::createWithSystemFont(text,
				String::createWithFormat("Fonts/%s.ttf", font)->getCString(),
				DEFAULT_FONT_SIZE);
#endif
	}

	void initWithGlobalFont(const char* text) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        aLabel = Label::createWithSystemFont(text, "Code Bold", DEFAULT_FONT_SIZE);
#else
		aLabel =
				Label::createWithSystemFont(text,
						String::createWithFormat("Fonts/%s.ttf", GLOBAL_FONT)->getCString(),
						DEFAULT_FONT_SIZE);
#endif
	}

	Label* aLabel;
};

class AssetManager {
public:

	Sprite* globalSprite(const char *name) {
		const char* path = String::createWithFormat("Scenes/Global/%s.png",
				name)->getCString();
		return Sprite::create(path);
	}

	void addBackground(Node *toNode) {
		Sprite* background = sprite("Background", VisibleRect::center());
		toNode->addChild(background);
	}

	LabelBuilder* label(const char *text) {
		return LabelBuilder::label(text);
	}

	Sprite* globalSprite(const char *name, Point position) {
		Sprite* sp = globalSprite(name);
		sp->setPosition(position);
		return sp;
	}

	virtual Sprite* sprite(const char* name, Point position) {
		Sprite* sp = sprite(name);
		sp->setPosition(position);
		return sp;
	}

	virtual Sprite* sprite(const char* name) {
		return Sprite::create(image(name));
	}

	virtual MenuItemSprite* menuItemSprite(const char* spriteName,
			const ccMenuCallback & callback, Point point) {
		std::string spriteString = std::string(spriteName);
		std::string spritePressedString = spriteString + "Pressed";
		auto item = CCMenuItemSprite::create(sprite(spriteName),
				sprite(spritePressedString.c_str()), callback);
		item->setPosition(point);
		return item;
	}

	void playSoundEffect(const char *name) {
		SoundManager::sharedSoundManager()->playSoundEffect(name);
	}

	virtual ~AssetManager() {
	}

protected:

	virtual const char* getResourceDirectory() = 0;

	const char* image(const char *name) {
		return String::createWithFormat("Scenes/%s/%s.png",
				getResourceDirectory(), name)->getCString();
	}
};

#endif /* RESOURCEFINDER_H_ */
