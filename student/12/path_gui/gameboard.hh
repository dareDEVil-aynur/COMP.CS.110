#ifndef GAMEBOARD_HH
#define GAMEBOARD_HH

#include <vector>
#include <QGraphicsScene>

// Possible slots in the gameboard
enum TileType {RED, GREEN, EMPTY, UNUSED};

// Type of the gameboard
using RowType = std::vector<TileType>;
using GridMatrix = std::vector<RowType>; // vector<vector<TileType>>

// Size of the gameboard
const unsigned int ROWS = 5;
const unsigned int COLUMS = 4;

// Type for the locations in the gameboard
struct Point
{
    int x; // column
    int y; // row
    bool operator==(const Point& rhs) const
    {
        return x == rhs.x and y == rhs.y;
    }
};

class PathBoard : public QGraphicsScene
{
public:
    PathBoard(QObject* parent = nullptr);
    ~PathBoard();

    // Prints the grid
    void displayBoard();

    // If possible, moves a button in the given grid
    // from start point to destination point.
    // A move may consists of horizontal and vertical steps.
    bool move(const Point& start, const Point& destination);

    // Checks if the game is over.
    // Returns true, if all red buttons are on the top row and all green buttons
    // are on the bottom row, otherwise returns false.
    bool is_game_over();

    // Returns the slot occupying the given point.
    TileType identifyTile(const Point& point);

    // Checks the validity of the given point.
    // Returns true if the point is inside the game grid, otherwise returns false.
    bool isValidCoordinate(const Point p);

    Q_OBJECT

signals:
    //Click signal to determine selected piece.
    void mouseClicked(QPointF point);

protected:
    //mousePressEvent override function to emit a custom signal that will
    //be collected in MainWindow class.
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

private:
    // Initializes a row, all buttons with the given color.
    // Used for initializing the top and bottom rows.
    RowType initializeRowWithColor(TileType color);

    // Initializes the game grid such that all green buttons are
    // on the top row and all red buttons are on the bottom rows.
    // Empty places and unused places are as in the figure given in the assignment.
    void initializeGrid();

    // If possible, makes a horizontal move in the given grid along the given row
    // from column1 to column2.
    // Returns true if the move is possible, otherwise returns false.
    bool makeHorizontalMove(unsigned int row, unsigned int column1,
                         unsigned int column2);

    // If possible, makes a vertical move in the given grid along the second
    // column from row1 to row2.
    // Returns true if the move is possible, otherwise returns false.
    bool makeVerticalMove(unsigned int row1, unsigned int row2);

    // Checks if all buttons on the given row are of the same (given) color.
    // Returns true, if they are of the same color, otherwise returns false.
    bool allSlotsOfSameColor(const RowType& r, TileType color);

    // Gameboard
    std::vector<std::vector<TileType>> gameMatrix_;
};

#endif // GAMEBOARD_HH
