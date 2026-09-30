# Interactive Graph Editor & Visualizer

## Project Overview
This project is a desktop application developed in C++ that serves as an interactive editor and visualizer for graph algorithms. The objective is to provide a practical tool for studying graph theory. Users can construct graphs dynamically on a visual canvas and observe the step-by-step execution of fundamental algorithms in real time. 

## Architecture & Tech Stack
*   **Core Logic:** The application is written in C++.
*   **Graphics & UI:** The graphical interface relies on the `graphics.h` (WinBGIm) library to handle custom rendering, window management, and user input. 
*   **Data Structures:** The graph's internal state is managed via an adjacency matrix, allowing for efficient processing of node connections and edge weights.
*   **Design Pattern:** The codebase utilizes Object-Oriented programming principles. Custom classes, such as `Node` and `Frame`, abstract the UI components. This separates the mathematical coordinate mapping and screen rendering from the core algorithmic logic.

## Key Features

### Interactive Workspace
Users can place nodes on the canvas and draw edges to connect them using mouse inputs. The editor supports both directed and undirected graphs. The rendering logic includes geometric and trigonometric calculations to ensure directional arrows point precisely to the node's radius boundary rather than overlapping the center.

### Live Algorithmic Animations
Instead of instantly returning a static output, the application animates the algorithmic traversal. As algorithms execute, visited nodes change color (from red to green), providing a clear visual representation of the execution flow.

### Algorithm Implementation
The system includes classic traversal methods alongside advanced pathfinding and structural algorithms:
*   **BFS and DFS:** Breadth-First and Depth-First Search for standard graph traversal.
*   **Dijkstra's Algorithm:** Calculates and displays the shortest path from a selected starting node to all other reachable nodes.
*   **Prim's Algorithm:** Computes the minimum spanning tree for undirected graphs.
*   **Tarjan’s Algorithm:** Identifies and groups the strongly connected components within a graph.

### Bezier Curve Rendering
To maintain visual clarity in highly interconnected or complex graphs, the application features a toggleable "Bezier Mode". This setting replaces rigid straight lines with smooth Bezier curves, significantly improving the layout and readability of the workspace.

### Action Logging System
A dedicated on-screen interface panel records user interactions and state changes, such as placing a node, assigning an edge weight, or executing a specific algorithm. These logs are displayed dynamically and are also persistently saved to a local `.txt` file for future reference.

## Additional UI Elements
The application includes dynamic adaptations based on system time. For example, the software reads the local system clock and activates a specialized thematic menu interface if the current month is April, demonstrating flexibility in managing dynamic UI states.
