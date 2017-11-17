/*
 * Copyright (C) 2017 Damir Porobic <https://github.com/damirporobic>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include "PainterArrow.h"

#include <cmath>

PainterArrow::PainterArrow(const QPointF& pos, const QPen& attributes) :
    PainterLine(pos, attributes)
{
    mArrowHeadLength = 20;
    mArrowHeadWidth = 10;
    mArrowHeadMid = 17;
}

QRectF PainterArrow::boundingRect() const
{
    auto offset = mArrowHeadWidth;
    return QRectF(mLine->p1(), mLine->p2()).normalized().adjusted(-offset, -offset, offset, offset);
}

void PainterArrow::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    if (isLineToShort()) {
        return;
    }

    auto arrow = createArrow();
    arrow = positionAndRotateArrow(arrow);

    painter->setPen(attributes().color());
    painter->setBrush(attributes().color());
    painter->drawPolygon(arrow);

    paintDecoration(painter);
}

bool PainterArrow::isLineToShort() const
{
    return mLine->length() < mMinLength;
}

QPolygonF PainterArrow::createArrow() const
{
    QPointF p0(0, 0);
    QPointF p1(-mArrowHeadLength, mArrowHeadWidth);
    QPointF p2(-mArrowHeadMid, 1);
    QPointF p3(-mLine->length(), 1);
    QPointF p4(-mLine->length(), -1);
    QPointF p5(-mArrowHeadMid, -1);
    QPointF p6(-mArrowHeadLength,-mArrowHeadWidth);

    QPolygonF arrow;
    arrow << p0 << p1 << p2 << p3 << p4 << p5 << p6;
    return arrow;
}

QPolygonF PainterArrow::positionAndRotateArrow(const QPolygonF& arrowHead) const
{
    auto endX = mLine->p2().x();
    auto endY = mLine->p2().y();
    auto angle = -mLine->angle();
    return QTransform().translate(endX, endY).rotate(angle).map(arrowHead);
}
