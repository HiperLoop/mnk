import Mathlib.Data.Set.Basic

-- Defines what a line that corresponds to a winning length k is.
def Is_winning_line (k : ℕ) (L : Set Int) : Prop :=
  ∃ (Start : Int) (dir : Int), (dir = 1 ∨ dir = -1) ∧
  L = { c | ∃ (i : ℕ), i < k ∧ c = Start + i * dir }

-- Defines what a pairing strategy is.
structure PairingStrategy (k : ℕ) where
  pairs : Set (Set Int)
  is_pair : ∀ s ∈ pairs, ∃ a b, a ≠ b ∧ s = {a, b}
  disjoint_logic : ∀ s1 s2, s1 ∈ pairs → s2 ∈ pairs → s1 ≠ s2 → (∀ x, x ∈ s1 → x ∈ s2 → False)
  blocks_all : ∀ L, Is_winning_line k L → ∃ s ∈ pairs, s ⊆ L
