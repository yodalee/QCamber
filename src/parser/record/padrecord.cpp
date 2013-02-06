#include <QDebug>
#include <QPainter>
#include <cmath>
#include "record.h"
#include "context.h"
#include "symbolfactory.h"

PadRecord::PadRecord(FeaturesDataStore* ds, const QStringList& param):
  Record(ds)
{
  int i = 0;
  x = param[++i].toDouble();
  y = param[++i].toDouble();
  sym_num = param[++i].toInt();
  polarity = (param[++i] == "P")? P: N;
  dcode = param[++i].toInt();
  orient = (Orient)param[++i].toInt();
  QString sym_name = ds->symbolNameMap()[sym_num];
  symbol = SymbolFactory::create(sym_name);
}

QPainterPath PadRecord::painterPath(void)
{
  QPainterPath path = symbol->painterPath();
  path.translate(x, -y);

  return path;
  // XXX: rotation
}

void PadRecord::add(QGraphicsScene* scene)
{
  symbol->setPos(x, -y);
  scene->addItem(symbol);

  symbol->rotate((orient % 4) * -90);
  if (orient >= M_0) {
    symbol->scale(1, -1);
  }
}
