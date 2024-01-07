#include <QDebug>
#include <QApplication>
#include <QHeaderView>
#include <QApplication>
#include <QPushButton>

#include "mystringtable.h"

void MyStringTableDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    //такой себе костыль, чтобы побороть баг в старых версиях Qt
    QStyleOptionViewItemV4  itemOption = option;

    initStyleOption(&itemOption, index);

    if(_parent->SelColor().isValid() && (option.state & QStyle::State_Selected))
    {
        itemOption.state &= ~QStyle::State_Selected;
    }

    if(_parent->HideFoc() && (option.state & QStyle::State_HasFocus))
    {
        itemOption.state &= ~QStyle::State_HasFocus;
    }

//  QApplication::style()->drawControl(QStyle::CE_ItemViewItem, &itemOption, painter);
    QStyledItemDelegate::paint( painter, itemOption, index );

    if(_parent->SelColor().isValid() && (option.state & QStyle::State_Selected))
    {
        QBrush brush = QBrush(_parent->SelColor()); //viewOption.backgroundBrush;
        painter->fillRect(itemOption.rect, brush);
    }

/*

    QStyleOptionButton button;
    QRect r = option.rect;//getting the rect of the cell
    int x,y,w,h;
    x = r.left() + r.width() - 16; //the X coordinate
    y = r.top();                   //the Y coordinate
    w = 16;                        //button width
    h = 16;                        //button height
    button.rect = QRect(x,y,w,h);
    button.text = "..";
    button.state = QStyle::State_Enabled;

    QApplication::style()->drawControl( QStyle::CE_PushButton, &button, painter);
*/
}

MyHeaderView::MyHeaderView(QWidget *parent) : QHeaderView(Qt::Horizontal, parent)
{
#if QT_VERSION >= 0x050000
    setSectionsClickable(true);
#else
    setClickable(true);
#endif
}


void MyHeaderView::paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const
{
      QVariant bg = model()->headerData(logicalIndex, Qt::Horizontal, Qt::BackgroundRole);
//    QVariant tx = model()->headerData(logicalIndex, Qt::Horizontal, Qt::DisplayRole);



      painter->save();

//    QString text = qvariant_cast<QString>(tx);
//    painter->fillRect(rect, bg.value<QBrush>());

//    painter->fillRect(rect, bg.value<QBrush>());
//    painter->drawText(rect, Qt::AlignCenter, text);

    //QBrush brush = QBrush(Qt::red);
    //painter->setBackground(brush);
      QHeaderView::paintSection(painter, rect, logicalIndex);
      painter->restore();
//    painter->drawText(rect, Qt::AlignLeft, text);
    //if(bg.isValid())
    //    painter->fillRect(rect, bg.value<QBrush>());
    //QBrush brush = QBrush(Qt::red);
    //painter->fillRect(rect, brush);

      QColor bgc = qvariant_cast<QColor>(bg);

      if(bgc.isValid())
      {
        painter->fillRect(rect, QBrush(bgc));
      }
}


MyStringTableModel::MyStringTableModel(MyStringTable *parent) :
    QAbstractTableModel((QObject*)parent)
{
    _tab = parent;
}

QVariant MyStringTableModel::data(const QModelIndex & index,int role) const
{
    QVariant result;
    QColor   color;

    if(!index.isValid())
    {
        return result;
    }

    int r = index.row();
    int c = index.column();

    // цвет фона ячейки
    if (role == Qt::BackgroundRole)
    {
        color = _tab->CellColor(r,c);
        if(color.isValid()) return color;

        color = _tab->_rows[r].color;
        if(color.isValid()) return color;
    }

    // Если необходимо отобразить картинку - ловим роль Qt::DecorationRole
    if (role == Qt::DecorationRole)
    {
        QString imgname = _tab->ImgName(r,c);
        if(imgname!="") return _tab->ImgIcon(r,c); //QIcon(imgname);
        else return result;
    }

    // Если хотим отобразить CheckBox, используем роль Qt::CheckStateRole
    // если текущий вызов не относится к роли отображения, завершаем

    if(role == Qt::CheckStateRole)
    {

        if(_tab->_cols[c].chkbx) return _tab->Check(r,c);
    }

    if (role == Qt::DisplayRole)
    {
        result = _tab->Cell(r,c);
        return result;
    }

    if (role == Qt::EditRole)
    {
        result = _tab->Cell(r,c);
        return result;
    }

    return result;
    //return QAbstractItemModel::data(index,role);
}


bool MyStringTableModel::setData( const QModelIndex &index, const QVariant &value, int role)
{
//    qDebug() << "setData" << index << value.toString() << role;

    if(!index.isValid()) return false;

    int r = index.row();
    int c = index.column();

    // нас интересует только роль, сообщающая об изменении
    if (role == Qt::EditRole)
    {
        if(_tab->_rows[r].cells[c].text != value.toString())
        {
           _tab->_rows[r].cells[c].text = value.toString();
           _tab->setTextChanged(true);
        }
        emit(dataChanged(index, index));
        // данные приняты
        return true;
    }

    if (role == Qt::BackgroundRole)
    {
        QColor color = value.value<QColor>();
        if(_tab->_rows[r].cells[c].color != color)
        {
           _tab->_rows[r].cells[c].color = color;
        }
        emit(dataChanged(index, index));
        // данные приняты
        return true;
    }

    if (role == Qt::DisplayRole)
    {
        _tab->_rows[r].cells[c].text = value.toString();
        emit(dataChanged(index, index));
        // данные приняты
        return true;
    }

    if (role == Qt::CheckStateRole)
    {
        _tab->_rows[r].cells[c].check = value.toInt();
        emit(dataChanged(index, index));
        // данные приняты
        return true;
    }

    return false;
}

bool MyStringTableModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
    if (role == Qt::BackgroundRole)
    {
        QColor color = value.value<QColor>();

        if(orientation==Qt::Horizontal)
        {
            _tab->_cols[section].labbg=color;
        }
        else
        {
            _tab->_rows[section].labbg=color;
        }

        emit headerDataChanged(orientation,section,section);
        // данные приняты
        return true;
    }

    if (role == Qt::DisplayRole)
    {
        QString label = value.value<QString>();

        if(orientation==Qt::Horizontal)
        {
            _tab->_cols[section].label=label;
        }
        else
        {
            _tab->_rows[section].label=label;
        }

        emit headerDataChanged(orientation,section,section);
        return true;
    }

    return false;
}


Qt::ItemFlags MyStringTableModel::flags(const QModelIndex & index) const
{
    int r = index.row();
    int c = index.column();

    if(_tab->CellEdit(r,c))
        return Qt::ItemIsSelectable |  Qt::ItemIsEditable | Qt::ItemIsEnabled ;

    if(_tab->ColEdit(c))
        return Qt::ItemIsSelectable |  Qt::ItemIsEditable | Qt::ItemIsEnabled ;

    return QAbstractTableModel::flags(index);
}


QVariant MyStringTableModel::headerData ( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const
{
    if(role == Qt::DisplayRole)
    {
        if     (orientation == Qt::Horizontal) return _tab->_cols[section].label;
        else if(orientation == Qt::Vertical  ) return _tab->_rows[section].label;
    }
    else if(role == Qt::BackgroundColorRole)
    {
        if     (orientation == Qt::Horizontal) return _tab->_cols[section].labbg;
        else if(orientation == Qt::Vertical  ) return _tab->_rows[section].labbg;
    }

    return QAbstractTableModel::headerData (section, orientation, role);
}

int MyStringTableModel::rowCount(const QModelIndex &) const
{
    int v = _tab->RowCount();
    return v;
}

int MyStringTableModel::columnCount(const QModelIndex &) const
{
    int v = _tab->ColCount();
    return v;
}


MyStringTable::MyStringTable(QWidget *parent) :
    QTableView(parent)
{
    setStyleSheet("QHeaderView::section { background-color:lightgrey }");

    _changed = false;

    _hidefoc = false;

    _model = new MyStringTableModel(this);
    setModel(_model);

    setHorizontalHeader(new MyHeaderView(this));

    verticalHeader  ()->setDefaultSectionSize(18);

    horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    horizontalHeader()->setHighlightSections(false);
    horizontalHeader()->setMinimumSectionSize(1);

#if QT_VERSION >= 0x050000
    horizontalHeader()->setSectionResizeMode (QHeaderView::Fixed);
#else
    horizontalHeader()->setResizeMode(QHeaderView::Fixed);
#endif

    setWordWrap(false);

    setSelectionBehavior(QAbstractItemView::SelectRows);
    setSelectionMode(QAbstractItemView::SingleSelection);

    setItemDelegate(new MyStringTableDelegate(this));

    connect
            (
                horizontalHeader(),
                SIGNAL(sectionPressed(int)),
                this,
                SLOT(hHeaderPressed(int))
                );
}

void MyStringTable::setIndexWidget(int r, int c,  QWidget *w)
{
     QTableView::setIndexWidget(_model->index(r, c), w);
}

void MyStringTable::setRowCount(int v, bool reset)
{
    int n;

    _model->beginResetModel();

    _rows.resize(v);

    for(n=0;n<_rows.count();n++) _rows[n].cells.resize(ColCount());

    if(reset) _model->endResetModel();

}

void MyStringTable::delRow(int row, bool reset)
{
    int i;
    int n = RowCount();

    if(row<0 || row>=n) return;

    _model->beginResetModel();

    QVector<MyStringTableRow> rows = _rows;

    _rows.resize(n-1);

    for(i=n=0;n<rows.count();n++)
    {
        if(n==row) continue;
        _rows[i].cells = rows[n].cells; i++;
    }

    if(reset) _model->endResetModel();
}



void MyStringTable::setColCount(int v, bool reset)
{
    int n;

    _model->beginResetModel();

    for(n=0;n<_rows.count();n++) _rows[n].cells.resize(v);
    _cols.resize(v); update();

    if(reset) _model->endResetModel();

}


QSize MyStringTable::sizeHint() const
{
    return QSize(200,100);
}


QColor  MyStringTable::SelColor()
{
    return _selcolor;
}

void MyStringTable::setSelColor(QColor v)
{
    _selcolor = v; update();
}

bool    MyStringTable::HideFoc()
{
    return _hidefoc;
}

void MyStringTable::setHideFoc(bool  v)
{
    _hidefoc = v; update();
}


int MyStringTable::RowCount()
{
    return _rows.count();
}

int MyStringTable::ColCount()
{
    return _cols.count();
}


QString MyStringTable::Cell(int r, int c)
{
    if(r<0 || r>=RowCount()) return "";
    if(c<0 || c>=ColCount()) return "";


    int rc = receivers(SIGNAL(cellDataRequest(int, int, QString&)));
    if(rc<1) return _rows[r].cells[c].text;

    QString v;

    emit cellDataRequest(r,c,v);

    return  v;
}

void MyStringTable::setCell(int r, int c, QString v)
{
    if(r<0 || r>=RowCount()) return;
    if(c<0 || c>=ColCount()) return;

    _model->setData(_model->index(r,c),v,Qt::EditRole);
}

QString MyStringTable::ImgName(int r, int c)
{
    if(r<0 || r>=RowCount()) return "";
    if(c<0 || c>=ColCount()) return "";

    return _rows[r].cells[c].imgnm;
}

QIcon MyStringTable::ImgIcon(int r, int c)
{
    if(r<0 || r>=RowCount()) return QIcon();
    if(c<0 || c>=ColCount()) return QIcon();

    return _rows[r].cells[c].icon;
}


void MyStringTable::setImgName(int r, int c, QString v)
{
    if(r<0 || r>=RowCount()) return;
    if(c<0 || c>=ColCount()) return;

    _rows[r].cells[c].imgnm = v;
    _rows[r].cells[c].icon = QIcon(v);
}


void MyStringTable::setImgIcon(int r, int c, QIcon v)
{
    if(r<0 || r>=RowCount()) return;
    if(c<0 || c>=ColCount()) return;

    _rows[r].cells[c].imgnm = "__ICON__";
    _rows[r].cells[c].icon  = v;
}


bool MyStringTable::CellEdit(int r, int c)
{
    if(r<0 || r>=RowCount()) return false;
    if(c<0 || c>=ColCount()) return false;

    return _rows[r].cells[c].edit;
}


void MyStringTable::setCellEdit(int r, int c, bool v)
{
    if(r<0 || r>=RowCount()) return;
    if(c<0 || c>=ColCount()) return;

    _rows[r].cells[c].edit = v;
}


QColor MyStringTable::CellColor(int r, int c)
{
    if(r<0 || r>=RowCount()) return QColor();
    if(c<0 || c>=ColCount()) return QColor();

    return _rows[r].cells[c].color;
}


void MyStringTable::setCellColor(int r, int c, QColor v)
{
    if(r<0 || r>=RowCount()) return;
    if(c<0 || c>=ColCount()) return;

    _model->setData(_model->index(r,c),v,Qt::BackgroundRole);
}


void MyStringTable::setColCheck(int c, int v)
{
    if(c<0 || c>=ColCount()) return;

    int r;

    for(r=0;r<RowCount();r++)
    {
        _model->setData(_model->index(r,c),v,Qt::CheckStateRole);
    }
}



void MyStringTable::setCheck(int r, int c, int v)
{
    if(r<0 || r>=RowCount()) return;
    if(c<0 || c>=ColCount()) return;

    //_rows[r].cells[c].check = v; //_model->updateRow(r);
    _model->setData(_model->index(r,c),v,Qt::CheckStateRole);
}


int MyStringTable::Check(int r, int c)
{
    if(r<0 || r>=RowCount()) return 4;
    if(c<0 || c>=ColCount()) return 4;

    return _rows[r].cells[c].check;
}


void MyStringTable::setTag(int r, int c, int64_t v)
{
    if(r<0 || r>=RowCount()) return;
    if(c<0 || c>=ColCount()) return;

    _rows[r].cells[c].tag = v;
}

int64_t MyStringTable::Tag(int r, int c)
{
    if(r<0 || r>=RowCount()) return -1;
    if(c<0 || c>=ColCount()) return -1;

    return _rows[r].cells[c].tag;
}


void MyStringTable::setColor(QColor v)
{
    _color=v; update();
}

void MyStringTable::setTextc(QColor v)
{
    _textc=v; update();
}


void MyStringTable::setRowColor(int r, QColor v)
{
    if(r<0 || r>=RowCount()) return;

    int n;

    for(n=0;n<ColCount();n++) setCellColor(r,n,v);
}

void MyStringTable::setRowTextc(int r, QColor v)
{
    if(r<0 || r>=RowCount()) return;

    _rows[r].textc=v;

}

void MyStringTable::setRowLabel(int r, QString v)
{
    if(r<0 || r>=RowCount()) return;

    _model->setHeaderData(r,Qt::Vertical,v,Qt::DisplayRole);
}

void MyStringTable::setColLabBg(int c, QColor v)
{
    // c < 0 - set all
    int n;

    if(c>=ColCount()) return;

    if(c<0)
    {
        for(n=0;n<ColCount();n++)
        {
            _model->setHeaderData(n,Qt::Horizontal,v,Qt::BackgroundRole);
        }
    }
    else
    {
       v.setAlpha(128);
        _model->setHeaderData(c,Qt::Horizontal,v,Qt::BackgroundRole);
    }
}


void MyStringTable::setColChkbx(int c, bool v)
{
    if(c<0 || c>=ColCount()) return;

    _cols[c].chkbx=v;  update();
}

bool MyStringTable::ColChkbx(int c)
{
    if(c<0 || c>=ColCount()) return false;

    return _cols[c].chkbx;
}

void MyStringTable::setColWidth(int c, int v)
{
    if(c<0 || c>=ColCount()) return;

    _cols[c].width=v;  update();
}

int MyStringTable::ColWidth(int c)
{
    if(c<0 || c>=ColCount()) return false;

    return _cols[c].width;
}


void MyStringTable::setColLabel(int c, QString v)
{
    if(c<0 || c>=ColCount()) return;

    _model->setHeaderData(c,Qt::Horizontal,v,Qt::DisplayRole);
}

QString MyStringTable::ColLabel(int c)
{
    if(c<0 || c>=ColCount()) return "";

    return _cols[c].label;
}

void MyStringTable::resizeEvent(QResizeEvent * event)
{
    int w = event->size().width();

    if(ColCount()>0)
    {
        int ws = w / ColCount();
        int ns;
        int ww = 0;
        int nn = 0;

        for(ns=0;ns<ColCount();ns++)
        {
            ws = ColWidth(ns);
            if(ws>0) ww += ws;
            else     nn++;
        }

        if(nn>0)
        {
            ww = (w - ww) / nn; if(ww<10) ww=10;
        }

        for(ns=0;ns<ColCount();ns++)
        {
            ws = ColWidth(ns);
            if(ws<1) ws = ww;
            horizontalHeader()->resizeSection(ns,ws);
        }
    }
    QTableView::resizeEvent(event);
}

void MyStringTable::keyPressEvent(QKeyEvent*    event)
{
    QTableView::keyPressEvent(event);

    QItemSelectionModel *sel = selectionModel();

    if(!sel->hasSelection()) return;

    int key = event->key();

    if(key==Qt::Key_Enter || key==Qt::Key_Return)
    {
        int r = currentIndex().row();
        int c = currentIndex().column();

        if(ColEdit(c))
        {

            if(this->state()!=QAbstractItemView::EditingState)
            {
                edit(currentIndex());
            }
        }
        else
        {
            emit rowEvent(r, 2);
        }
    }
    else if(key==Qt::Key_Home)
    {
//      QApplication::beep();
        QModelIndex index = _model->index(0,0, QModelIndex());

        sel->clearSelection();
        setCurrentIndex(index);
    }
    else if(key==Qt::Key_End)
    {
        QModelIndex index = _model->index(RowCount()-1,0, QModelIndex());

        sel->clearSelection();
        setCurrentIndex(index);
    }
}



void MyStringTable::mousePressEvent (QMouseEvent * event)
{
    QTableView::mousePressEvent(event);

    QItemSelectionModel *sel = selectionModel();

    if(!sel->hasSelection()) return;

    QModelIndex idx = currentIndex();

    int c = idx.column();
    int r = idx.row();

    int ck = Check(r,c);

    if(ck) ck=0;
    else   ck=2;

    if(ColChkbx(c))
    {
        setCheck(r,c,ck);
        emit rowEvent(r, 4);
    }
}

void MyStringTable::mouseDoubleClickEvent(QMouseEvent * event)
{
    QTableView::mouseDoubleClickEvent(event);

    QItemSelectionModel *sel = selectionModel();

    if(!sel->hasSelection()) return;

    QModelIndexList list = sel->selectedRows();

    if(list.count()<1) return;

    int row = list.at(0).row();

    emit rowEvent(row, 2);
}

void MyStringTable::selectionChanged(const QItemSelection & selected, const QItemSelection & deselected)
{
    QAbstractItemView::selectionChanged(selected,deselected);

    QItemSelectionModel *sel = selectionModel();

    if(!sel->hasSelection()) return;

    QModelIndexList list = sel->selectedRows();

    if(list.count()<1) return;

    int row = list.at(0).row();

    emit rowEvent(row, 1);
}


void MyStringTable::setCurCell(int r, int c)
{
    QModelIndex index = _model->index(r,c, QModelIndex());
    setCurrentIndex(index);
}

int MyStringTable::curRow()
{
    QModelIndex index = currentIndex();
    return index.row();
}


int MyStringTable::curCol()
{
    QModelIndex index = currentIndex();
    return index.column();
}

void MyStringTable::editorDestroyed ( QObject * /*editor*/ )
{
}

void MyStringTable::setColEdit(int c, bool v)
{
    if(c<0 || c>=ColCount()) return;
    _cols[c].edit = v;
}


bool MyStringTable::ColEdit(int c)
{
    if(c<0 || c>=ColCount()) return false;
    return _cols[c].edit;
}

void MyStringTable::setData(int r, int c, QString v)
{
    if(r<0 || r>=RowCount()) return;
    if(c<0 || c>=ColCount()) return;

    _rows[r].cells[c].data = v;
}

QString MyStringTable::Data(int r, int c)
{
    if(r<0 || r>=RowCount()) return QString();
    if(c<0 || c>=ColCount()) return QString();

    return _rows[r].cells[c].data;
}

void MyStringTable::setTextChanged(bool v)
{
    _changed = v;

    if(v) emit textChanged();
}



