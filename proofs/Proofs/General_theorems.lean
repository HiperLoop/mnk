import Proofs.Definitions
import Mathlib.Data.Int.Basic
import Mathlib.Tactic.Linarith

/--
Proves that given a pairing strategy that has disjoint pairs and
blocks all winning directions the game is a draw in 1D.
-/
theorem pairing_prevents_win_1D {k : ℕ} (S : Pairing_strategy_1D k)
  (occupied_x occupied_o : Set Int)
  (h_no_overlap : ∀ z, z ∈ occupied_x → z ∈ occupied_o → False)
  (h_mirror : ∀ s ∈ S.pairs, ∀ a b, a ≠ b → s = {a, b} → (a ∈ occupied_x ↔ b ∈ occupied_o)) :
  ∀ L, Is_winning_line_1D k L → ¬ (L ⊆ occupied_x) := by
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

/--
Proves that given a pairing strategy that has disjoint pairs and
blocks all winning directions the game is a draw in 2D.
-/
theorem pairing_prevents_win_2D {k : ℕ} (S : Pairing_strategy_2D k)
  (occupied_x occupied_o : Set Coord)
  (h_no_overlap : ∀ z, z ∈ occupied_x → z ∈ occupied_o → False)
  (h_mirror : ∀ s ∈ S.pairs, ∀ a b, a ≠ b → s = {a, b} → (a ∈ occupied_x ↔ b ∈ occupied_o)) :
  ∀ L, Is_winning_line_2D k L → ¬ (L ⊆ occupied_x) := by
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

theorem addidng_to_end_leads_to_k_plus_1 {k : ℕ} (L : Set Coord) (hL : Is_winning_line_2D k L) :
  ∃ c : Coord, Is_winning_line_2D (k + 1) (L ∪ {c}) := by
  rcases hL with ⟨Start, dir, h_dir, h_L⟩
  let c := (Start.1 + k * dir.1, Start.2 + k * dir.2)
  use c
  rw [h_L]
  use Start, dir
  constructor;
  · exact h_dir
  ext x
  constructor
  · rintro (⟨i, hi0, hik, rfl⟩ | rfl)
    · refine ⟨i, hi0, ?_, rfl⟩
      omega
    · refine ⟨(k : ℤ), by exact_mod_cast Nat.zero_le k, ?_, by exact rfl⟩
      have hk : (k : ℤ) < ((k + 1 : ℕ) : ℤ) := by
        exact_mod_cast Nat.lt_succ_self k
      simp
  · rintro ⟨i, hi0, hik1, rfl⟩
    have hik_le : i ≤ (k : ℤ) := by
      omega
    rcases lt_or_eq_of_le hik_le with hik | rfl
    · exact Or.inl ⟨i, hi0, hik, rfl⟩
    · exact Or.inr (by simp [c])
