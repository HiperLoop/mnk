import Mathlib.Data.Set.Basic

-- 1D
-- Defines what a line that corresponds to a winning length k is in 1D.
def Is_winning_line_1D (k : ℕ) (L : Set Int) : Prop :=
  ∃ (Start : Int) (dir : Int), (dir = 1 ∨ dir = -1) ∧
  L = { c | ∃ (i : ℕ), i < k ∧ c = Start + i * dir }

-- Defines what a pairing strategy is in 1D.
structure Pairing_strategy_1D (k : ℕ) where
  pairs : Set (Set Int)
  is_pair : ∀ s ∈ pairs, ∃ a b, a ≠ b ∧ s = {a, b}
  disjoint_logic : ∀ s1 s2, s1 ∈ pairs → s2 ∈ pairs → s1 ≠ s2 → (∀ x, x ∈ s1 → x ∈ s2 → False)
  blocks_all : ∀ L, Is_winning_line_1D k L → ∃ s ∈ pairs, s ⊆ L

-- 2D
def Coord := Int × Int

-- Defines what a line that corresponds to a winning length k is in 2D.
def Is_winning_line_2D (k : ℕ) (L : Set Coord) : Prop :=
  ∃ (start : Coord) (dir : Int × Int),
    (dir.1 ≠ 0 ∨ dir.2 ≠ 0) ∧
    L = { p | ∃ (i : ℤ), 0 ≤ i ∧ i < k ∧ p = (start.1 + i * dir.1, start.2 + i * dir.2) }

-- Defines what a pairing strategy is in 2D.
structure Pairing_strategy_2D (k : ℕ) where
  pairs : Set (Set Coord)
  is_pair : ∀ s ∈ pairs, ∃ a b, a ≠ b ∧ s = {a, b}
  disjoint_logic : ∀ s1 s2, s1 ∈ pairs → s2 ∈ pairs → s1 ≠ s2 → (∀ x, x ∈ s1 → x ∈ s2 → False)
  blocks_all : ∀ L, Is_winning_line_2D k L → ∃ s ∈ pairs, s ⊆ L

-- General
def Is_in_same_line (p1 p2 : Coord) : Prop :=
  (p1.1 = p2.1) ∨ (p1.2 = p2.2) ∨ (p1.1 - p1.2 = p2.1 - p2.2) ∨ (p1.1 + p1.2 = p2.1 + p2.2)

def Is_in_same_line_with_dir (p1 p2 : Coord) (dir : Int × Int) : Prop :=
  ∃ i j, i ≠ j ∧ p1 = (p1.1 + i * dir.1, p1.2 + i * dir.2) ∧
  p2 = (p1.1 + j * dir.1, p1.2 + j * dir.2)

def Is_line (L : Set Coord) : Prop :=
  ∃ dir : Coord, (dir.1 ≠ 0 ∨ dir.2 ≠ 0) ∧ (∀ p1 ∈ L, ∀ p2 ∈ L, Is_in_same_line_with_dir p1 p2 dir)
