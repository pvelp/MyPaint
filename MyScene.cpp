#include "myscene.h"
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QPen>
#include <QKeyEvent>
#include <QGraphicsPathItem>

MyScene::MyScene(QObject *parent)
    :QGraphicsScene(parent)
    ,_current_figure_type(Line)
    ,_current_draw_item(nullptr)
    ,_color_square(Qt::white)
    ,_color_circuit(Qt::black)
    ,_size(1)
    ,_fill_shape(false)
    ,_start_position()
{
}

MyScene::~MyScene()
{
    delete this;
}

void MyScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (_current_draw_item){
        switch (_current_draw_item->type()) {
        case QGraphicsRectItem::Type:
        {
            QGraphicsRectItem *rect_item = (QGraphicsRectItem*)_current_draw_item;

            QPointF point1 = _start_position;
            QPointF point2 = event->scenePos();

            QRectF new_rect(QPointF(qMin(point1.x(), point2.x()), qMin(point1.y(), point2.y())),
                            QPointF(qMax(point1.x(), (point2.x())), qMax(point1.y(), point2.y())));

            rect_item->setRect(new_rect);

            break;
        }
        case QGraphicsEllipseItem::Type:
        {
            QGraphicsEllipseItem *ellipse_item = (QGraphicsEllipseItem*)_current_draw_item;
            QRectF ellipse = ellipse_item->rect();
            ellipse.setBottomRight(event->scenePos());
            ellipse_item->setRect(ellipse);
            break;
        }
        case QGraphicsPathItem::Type:
        {
            QGraphicsPathItem *pi = (QGraphicsPathItem*)_current_draw_item;
            QPainterPath pp = pi->path();
            pp.lineTo(event->scenePos());
            pi->setPath(pp);
            break;
        }
        default:
            break;
        }
    }
}

void MyScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (_current_draw_item == nullptr){
        _start_position = event->scenePos();
        switch (_current_figure_type) {
        case Rect:
        {
            QGraphicsRectItem *item = new QGraphicsRectItem(event->scenePos().x(), event->scenePos().y(), 0, 0);
            if(_fill_shape){
                item->setBrush(_color_square);
            }
            _params.setColor(_color_circuit);
            _params.setWidth(_size);
            item->setPen(_params);
            addItem(item);
            _current_draw_item = item;
            break;
        }
        case Ellipse:
        {
            QGraphicsEllipseItem *item = new QGraphicsEllipseItem(event->scenePos().x(), event->scenePos().y(), 0, 0);
            if(_fill_shape){
                item->setBrush(_color_square);
            }
            _params.setColor(_color_circuit);
            _params.setWidth(_size);
            item->setPen(_params);
            addItem(item);
            _current_draw_item = item;
            break;
        }
        case Line:
        {
            QPainterPath pp;
            pp.moveTo(event->scenePos());
            QGraphicsPathItem *item = new QGraphicsPathItem(pp);
            item->setPath(pp);
            _params.setColor(_color_circuit);
            _params.setWidth(_size);
            item->setPen(_params);
            addItem(item);
            _current_draw_item = item;
            break;
        }
        default:
            break;
        }
    }
    QGraphicsScene::mousePressEvent(event);
}

void MyScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (_current_draw_item){
        _current_draw_item = nullptr;
    }
    QGraphicsScene::mouseReleaseEvent(event);
}

int MyScene::size() const
{
    return _size;
}

void MyScene::setSize(int size)
{
    _size = size;
}

void MyScene::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();
    if(key == Qt::Key_Escape){
        this->removeItem(_current_draw_item);
    }
}

QPointF MyScene::previous_point() const
{
    return _previous_point;
}

void MyScene::setPrevious_point(const QPointF &previous_point)
{
    _previous_point = previous_point;
}

QGraphicsItem *MyScene::current_draw_item() const
{
    return _current_draw_item;
}

void MyScene::setCurrent_draw_item(QGraphicsItem *current_draw_item)
{
    _current_draw_item = current_draw_item;
}

QColor MyScene::color_circuit() const
{
    return _color_circuit;
}

void MyScene::setColor_circuit(const QColor &color_circuit)
{
    _color_circuit = color_circuit;
}

bool MyScene::fill_shape() const
{
    return _fill_shape;
}

void MyScene::setFill_shape(bool fill_shape)
{
    _fill_shape = fill_shape;
}

MyScene::FigureType MyScene::current_figure_type() const
{
    return _current_figure_type;
}

void MyScene::setCurrent_figure_type(FigureType current_figure_type)
{
    _current_figure_type = current_figure_type;
}

void MyScene::set_color_square(QColor color)
{
    _color_square = color;
}
