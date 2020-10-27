#include "OpenItem.h"



OpenItem::OpenItem()
{
}


OpenItem::~OpenItem()
{
}

void OpenItem::move(sf::Vector2f v2f) {
	m_rec.setPosition(v2f);
}