/*
 * Copyright (C) 2018 Damir Porobic <https://github.com/damirporobic>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include "LinuxSnippingArea.h"

LinuxSnippingArea::LinuxSnippingArea() : AbstractSnippingArea()
{
	setWindowFlags(windowFlags() | Qt::Tool | Qt::X11BypassWindowManagerHint);
}

QRect LinuxSnippingArea::selectedRectArea() const
{
	auto scaleFactor = DesktopScaleFactorProvider::instance()->ScaleFactor();
    return { MathHelper::multiplyIntWithReal(mCaptureArea.x(), scaleFactor),
			 MathHelper::multiplyIntWithReal(mCaptureArea.y(), scaleFactor),
			 MathHelper::multiplyIntWithReal(mCaptureArea.width(), scaleFactor),
			 MathHelper::multiplyIntWithReal(mCaptureArea.height(),scaleFactor) };
}

void LinuxSnippingArea::setFullScreen()
{
	QRect fullScreenRect;
	auto screenCount = QDesktopWidget().screenCount();
	for(int i = 0; i < screenCount; i++) {
		auto screenRect = QDesktopWidget().screenGeometry(i);
		fullScreenRect = fullScreenRect.united(screenRect);
	}

	setGeometry(fullScreenRect);
	QWidget::show();
}

QPoint LinuxSnippingArea::getMousePosition() const
{
	return mapFromGlobal(QCursor::pos());
}

QRect LinuxSnippingArea::getSnippingAreaGeometry() const
{
	auto snippingAreaGeometry = geometry();
	return {mapFromGlobal(snippingAreaGeometry.topLeft()), mapFromGlobal(snippingAreaGeometry.bottomRight())};
}