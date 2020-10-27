#include "CaverItem.h"



CaverItem::CaverItem()
{
}


CaverItem::~CaverItem()
{
}

void CaverItem::move(sf::Vector2f v2f) {
	if (num % 2 == 0) {
		m_rec.setPosition(m_rec.getPosition().x - m_rec.getSize().x , m_rec.getPosition().y);
	}
	else {
		m_rec.setPosition(m_rec.getPosition().x + m_rec.getSize().x, m_rec.getPosition().y);
	}
	num++;
}