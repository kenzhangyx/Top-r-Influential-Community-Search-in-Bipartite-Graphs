# Top-R Influential Community Search in Bipartite Graph

This repository provides the implementation of multiple algorithms for finding the top-r influential communities in a bipartite graph. The code includes both accurate and approximate solutions, using different methods to enhance efficiency and accuracy. Below is a structured overview of the project.

## Project Structure
TopRInfluentialCommunity/  
│  
├── all_mains/  
│   ├── main.cpp                # Naive solution  
│   ├── main_bound.cpp          # Naive solution + Upper Bound  
│   ├── main_fit.cpp            # Naive solution + SlimTree  
│   └── main_fit_bound.cpp      # Combination of all advanced methods  
│  
├── include/                    # Header files for data structures used in bipartite graph implementation  
│   └── …  
│  
├── src/                        # Source files for core graph functionality  
│   └── …  
│  
├── New_framework_beta.cpp      # Approximate solution with optimizations  
├── newframeworks.cpp           # Approximate solution using naive method  
└── README.md                   # Project documentation (you’re reading this!)  
### Overview Diagram

Below is a visual representation of the structure and relationships of the project components:  
                       +----------------------+  
                       |  TopRInfluentialCommunity  |  
                       +-----------+--------------+  
                                   |  
            +----------------------+----------------------+  
            |                                               |  
   +--------+--------+                          +-----------+-----------+  
   |  Accurate Methods  |                          | Approximate Methods   |  
   +---------------------+                          +-----------------------+  
            |                                                |  
 +----------+-----------+                       +------------+------------+  
 | all_mains Folder      |                       |  New_framework_beta.cpp |  
 |                      |                       |  newframeworks.cpp       |  
 +----------+-----------+                       +--------------------------+  
            |  
+———––+–––––––------+  
| main.cpp          | -> Naive Solution  
| main_bound.cpp    | -> Naive + Upper Bound  
| main_fit.cpp      | -> Naive + SlimTree  
| main_fit_bound.cpp| -> Combination of All  
+—————————–+  
![QQ_1728232914648](https://github.com/user-attachments/assets/de00018b-0d74-4369-88a8-277d7da94409)

### Contents

#### 1. **Accurate Methods** (`all_mains/`)

This folder contains four different codes, each designed to solve the problem with increasing efficiency and complexity. Each file in this folder employs a specific combination of advanced methods:

- **`main.cpp`**: Implements the **naive solution** for finding the top-r influential community in the bipartite graph.
- **`main_bound.cpp`**: Enhances the naive method by adding an **upper bound** to improve the search efficiency.
- **`main_fit.cpp`**: Combines the naive method with the **SlimTree** technique to efficiently prune the solution space.
- **`main_fit_bound.cpp`**: A **combination of all the above advanced methods**, including naive, upper bound, and SlimTree optimizations, to provide a comprehensive and accurate solution.

#### 2. **Graph Data Structure** (`include/` and `src/`)

- The `include/` folder contains the header files, while the `src/` folder includes the source code files that provide the data structures needed to represent and work with **bipartite graphs**.
- These components abstract the internal representation and operations related to the bipartite graph, such as adding nodes, edges, and maintaining graph properties.

#### 3. **Approximate Methods**

These files provide **approximate solutions** for faster but less precise results:

- **`newframeworks.cpp`**: Implements an **approximate solution** using a **naive approach** for finding the influential community.
- **`New_framework_beta.cpp`**: An advanced version of `newframeworks.cpp`, this file employs additional **optimization techniques** to provide approximate results more efficiently.

### How to Use

1. **Accurate Search**:
   - For accurate results, use the codes in the `all_mains/` folder.
   - The simplest approach can be found in `main.cpp`, while the most optimized one is in `main_fit_bound.cpp`.

2. **Approximate Search**:
   - For faster, approximate results, you can use either `newframeworks.cpp` (naive approach) or `New_framework_beta.cpp` (optimized approach).

### Future Work

- Expand the approximate methods with other heuristic techniques for better precision.
- Explore parallelism and GPU acceleration for optimizing large graph searches.

### Contact Information

For any questions or contributions, feel free to create an issue or submit a pull request.
