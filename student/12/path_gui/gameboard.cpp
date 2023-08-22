#include "gameboard.hh"
#include <iostream>
#include <QGraphicsSceneMouseEvent>

PathBoard::PathBoard(QObject* parent)
    : QGraphicsScene(parent)
{
    initializeGrid();
}

PathBoard::~PathBoard()
{

}

void PathBoard::displayBoard()
{
    std::cout << "===============" << std::endl;
    std::cout << "|   | 1 2 3 4 |" << std::endl;
    std::cout << "---------------" << std::endl;
    for(unsigned int i = 0; i < gameMatrix_.size(); ++i)
    {
        std::cout << "| " << i + 1 << " | ";
        for(unsigned int j = 0; j < gameMatrix_.at(i).size(); ++j)
        {
            switch(gameMatrix_.at(i).at(j))
            {
            case GREEN: std::cout << "G "; break;
            case RED: std::cout << "R "; break;
            case EMPTY: std::cout << "o "; break;
            case UNUSED: std::cout << "  "; break;
            }
        }
        std::cout << "|" << std::endl;
    }
    std::cout << "===============" << std::endl;
}

bool PathBoard::move(const Point &start, const Point &destination)
{
    GridMatrix orig = gameMatrix_;
    // Horizontal move only
    if(start.y == destination.y)
    {
        return makeHorizontalMove(destination.y, start.x, destination.x);
    }

    // Button is moved step by step, and thus, we need a new start point
    // that is updated after each step.
    Point new_start = start;

    // Trying to move start point to the crossing from where to continue
    // vertically
    if(start.y % 2 == 0 and not makeHorizontalMove(start.y, start.x, 1))
    {
        gameMatrix_ = orig;
        return false;
    }
    new_start.x = 1;

    // Vertical move along the only possible column (the second one)
    if(not makeVerticalMove(new_start.y, destination.y))
    {
        gameMatrix_ = orig;
        return false;
    }
    new_start.y = destination.y;

    // Trying to move destination point to the crossing from where to continue
    // vertically
    if(destination.y % 2 == 0 and
       not makeHorizontalMove(destination.y, new_start.x, destination.x))
    {
        gameMatrix_ = orig;
        return false;
    }
    return true;
}

bool PathBoard::is_game_over()
{
    if(not allSlotsOfSameColor(gameMatrix_.at(0), RED))
    {
        return false;
    }
    if(not allSlotsOfSameColor(gameMatrix_.at(ROWS - 1), GREEN))
    {
        return false;
    }
    return true;
}

TileType PathBoard::identifyTile(const Point &point)
{
    return gameMatrix_.at(point.y).at(point.x);
}

bool PathBoard::isValidCoordinate(const Point p)
{
    if(p.x < 0 or p.x >= static_cast<int>(COLUMS))
    {
        return false;
    }
    if(p.y < 0 or p.y >= static_cast<int>(ROWS))
    {
        return false;
    }
    return true;
}

//Added customized handler for mouse clicks
void PathBoard::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    QPointF point = event->scenePos();
    emit mouseClicked(point);
}

RowType PathBoard::initializeRowWithColor(TileType color)
{
    RowType result;
    for(unsigned int i = 0; i < COLUMS; ++i)
    {
        result.push_back(color);
    }
    return result;
}

void PathBoard::initializeGrid()
{
    // Initializing top row
    gameMatrix_.push_back(initializeRowWithColor(GREEN));

    // Setting all middle places as unused
    for(unsigned int i = 0; i < ROWS - 2; ++i)
    {
        RowType row;
        for(unsigned int j = 0; j < COLUMS; ++j)
        {
            row.push_back(UNUSED);
        }
        gameMatrix_.push_back(row);
        row.clear();
    }

    // Changing some of the places to be empty
    for(unsigned int i = 1; i < ROWS - 1; ++i)
    {
        gameMatrix_.at(i).at(1) = EMPTY;
    }
    gameMatrix_.at(2).at(2) = EMPTY;

    // Initializing the bottom row
    gameMatrix_.push_back(initializeRowWithColor(RED));
}

bool PathBoard::makeHorizontalMove(unsigned int row, unsigned int column1, unsigned int column2)
{
    // Identical columns => no move is needed
    if(column1 == column2)
    {
        return true;
    }

    // Moving from left to right (if possible),
    if(column1 < column2)
    {
        for(unsigned int i = column2; i > column1; --i)
        {
            if(gameMatrix_.at(row).at(i) != EMPTY)
            {
                return false;
            }
        }
    }

    // or moving from right to left (if possible)
    else if(column2 < column1)
    {
        for(unsigned int i = column2; i < column1; ++i)
        {
            if(gameMatrix_.at(row).at(i) != EMPTY)
            {
                return false;
            }
        }
    }

    // Moving the button, since it is possible
    gameMatrix_.at(row).at(column2) = gameMatrix_.at(row).at(column1);
    gameMatrix_.at(row).at(column1) = EMPTY;
    return true;
}

bool PathBoard::makeVerticalMove(unsigned int row1, unsigned int row2)
{
    // Identical rows => no move is needed
    if(row1 == row2)
    {
        return true;
    }

    // Moving from top to bottom (if possible),
    if(row1 < row2)
    {
        for(unsigned int i = row2; i > row1; --i)
        {
            if(gameMatrix_.at(i).at(1) != EMPTY)
            {
                return false;
            }
        }
    }

    // or moving from bottom to top (if possible)
    else if(row2 < row1)
    {
        for(unsigned int i = row2; i < row1; ++i)
        {
            if(gameMatrix_.at(i).at(1) != EMPTY)
            {
                return false;
            }
        }
    }

    // Moving the button, since it is possible
    gameMatrix_.at(row2).at(1) = gameMatrix_.at(row1).at(1);
    gameMatrix_.at(row1).at(1) = EMPTY;
    return true;
}

bool PathBoard::allSlotsOfSameColor(const RowType &r, TileType color)
{
    for(unsigned int i = 0; i < r.size(); ++i)
    {
        if(r.at(i) != color)
        {
            return false;
        }
    }
    return true;
}
