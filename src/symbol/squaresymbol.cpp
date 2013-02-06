#include "squaresymbol.h"

#include <QtGui>
#include <QRegExp>

SquareSymbol::SquareSymbol(QString def):
    Symbol("s", "s([0-9.]+)"), m_def(def)
{
  QRegExp rx(m_pattern);
  if (!rx.exactMatch(def))
    throw InvalidSymbolException(def.toAscii());
  QStringList caps = rx.capturedTexts();
  m_s = caps[1].toDouble() / 1000.0;

  painterPath();
}

QPainterPath SquareSymbol::painterPath(void)
{
  if (m_valid)
    return m_cachedPath;

  m_cachedPath = QPainterPath();
  m_valid = true;

  m_cachedPath.addRect(-m_s / 2, -m_s / 2, m_s, m_s);

  m_bounding = m_cachedPath.boundingRect();
  return m_cachedPath;
}
