# Solving a generalisation of tic-tac-toe or $k$-in-a-row game on infinite $\{m, n\}$ tilings of 2D space.
This is a math/CS project that tries to look at generalisations of the mnk-games on non-square tilings. We explore other Euclidean tilings such as the hexagonal tiling but also various hyperbolic tilings. The aim is to prove properties of mnk-games on these tilings and look if there is any emergent behaviour potentially useful in solving similar problems in the future.

**Link to project:** https://github.com/HiperLoop/mnk

## Project structure:

The project is compartmentalised by code type. Meaning, there is a folder for each unique programming languege or type of data used. These are the following folders:

- .vscode: compiler settings for C++ compiling in VS code
- Notes: article links and summaries, random notes relating to the project
- Proofs: Lean4 code with precise mathematical proofs of pairing strategies
- Src: C++ code for game logic and solvers to find winning strategies
- Tex: LaTeX code with figures folder, also with the generated PDF
- tstex_modules: settings for LaTeX compilation

## How It's Made:

**Tech used:** LaTeX, Lean4, C++

### LaTeX

LaTeX is used to gather the proofs and findings in an extensive formal article-style document also explaining the background information and the used mothodology.

### Lean4

The pairing strategy proofs of draws are formalised in Lean (**TODO**) to ensure they are mathematically sound. It also potentially alows others to use the theorems about the $mnk$-games we prove in the future. In lean we focus on the upper $k$ bound for fully solving the variants.

### C++

The C++ code is use to apply various tree-traversal or solving algorithms to the game variants to potentially find a winning strategy. These algorithms include:

- Proof number search (Mainly for sherical and platonic tilings with relatively small finite search spaces)
- Dependency based search (Used for redced infinite tilings)
- **TODO**

They have been proven to produce an unstoppable strategy and thus serve as proofs for the lower $k$-bound in the game-solving process.

## Findings:

*N/A* 