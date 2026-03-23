import Proofs.Definitions
import Mathlib.Data.Int.Basic
import Mathlib.Tactic.Linarith

/--
Proves that given a pairing strategy that has disjoint pairs and
blocks all winning directions the game is a draw.
-/
theorem pairing_prevents_win {k : ℕ} (S : PairingStrategy k)
  (occupied_x occupied_o : Set Int)
  (h_no_overlap : ∀ z, z ∈ occupied_x → z ∈ occupied_o → False)
  (h_mirror : ∀ s ∈ S.pairs, ∀ a b, a ≠ b → s = {a, b} → (a ∈ occupied_x ↔ b ∈ occupied_o)) :
  ∀ L, Is_winning_line k L → ¬ (L ⊆ occupied_x) := by
  intro L hL h_win_x
  rcases S.blocks_all L hL with ⟨s, hs_in, hs_sub⟩
  rcases S.is_pair s hs_in with ⟨a, b, h_ne, h_sep⟩
  have ha_x : a ∈ occupied_x := by
    apply h_win_x; apply hs_sub; rw [h_sep]; exact Or.inl rfl
  have hb_x : b ∈ occupied_x := by
    apply h_win_x; apply hs_sub; rw [h_sep]; exact Or.inr rfl
  have hb_o : b ∈ occupied_o := by
    rw [← (h_mirror s hs_in a b h_ne h_sep)]; exact ha_x
  exact h_no_overlap b hb_x hb_o
