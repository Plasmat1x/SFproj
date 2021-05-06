#include <SFML/Graphics.hpp>

namespace sfd {

    /// <summary>
    /// 
    /// </summary>
    /// <param name="win"></param>
    /// <param name="cols"> x count </param>
    /// <param name="rows"> y count </param>
    static void drawGrid(sf::RenderWindow& win, int cols, int rows, sf::Color color) {
        // initialize values
        int numLines = rows + cols - 2;
        sf::VertexArray grid(sf::Lines, 2 * (numLines));
        win.setView(win.getDefaultView());
        auto size = win.getView().getSize();
        float rowH = size.y / rows;
        float colW = size.x / cols;
        // row separators
        for (int i = 0; i < rows - 1; i++) {
            int r = i + 1;
            float rowY = rowH * r;
            grid[i * 2].position = { 0, rowY };
            grid[i * 2 + 1].position = { size.x, rowY };

            grid[i * 2].color = color;
            grid[i * 2 + 1].color = color;
        }
        // column separators
        for (int i = rows - 1; i < numLines; i++) {
            int c = i - rows + 2;
            float colX = colW * c;
            grid[i * 2].position = { colX, 0 };
            grid[i * 2 + 1].position = { colX, size.y };

            grid[i * 2].color = color;
            grid[i * 2 + 1].color = color;
        }
        // draw it
        win.draw(grid);
    }

    static void drawGrid(sf::RenderWindow& win, sf::Vector2f size_cell, sf::View& view, sf::Color color) {
        // initialize values
        auto size = view.getSize();
        int numLines = int((size.x / size_cell.x) + (size.y/ size_cell.y));
        sf::VertexArray grid(sf::Lines, 2 * (numLines));
        
        int rowC = size.y / size_cell.y;
        int colC = size.x / size_cell.x;
        // row separators
        for (int i = 0; i < rowC - 1; i++) {
            grid[i * 2].position = { 0, i * size_cell.y };
            grid[i * 2 + 1].position = { size.x, size_cell.y * i };

            grid[i * 2].color = color;
            grid[i * 2 + 1].color = color;
        }
        // column separators
        for (int i = 0; i < colC; ) {

            for (int j = rowC; j < numLines; j++)
            {
                grid[j * 2].position = { size_cell.x * i, 0 };
                grid[j * 2 + 1].position = { size_cell.x * i, size.y };

                grid[j * 2].color = color;
                grid[j * 2 + 1].color = color;

                i++;
            }
        }

        // draw it
        win.draw(grid);
    }
}

