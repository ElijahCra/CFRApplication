QT6 wrapper over https://github.com/ElijahCra/2PlayerCFR which handles the algorithm and training.

Each cell represents the optimal strategy for each hand in Pre-Flop Poker as determined by the CFR Algorithm. The size of each color tells how probable the first player is to take that action with green = bet, blue = check, black = fold.

Main Features:
Start: Runs the algorithm with batch size of 2000 for 400 iterations.
Pause: Pause current training run.
Stop: Cancel current training run, resets iteration count.

Warning:
This program eats up memory (due to storing a massive amount of nodes in ram) so don't run it too many times in a row.

Screenshots:
Pre-Training (Equal Probability / Fully Random Strategy)

<img src="https://github.com/user-attachments/assets/5364d690-d8ec-420d-8d2e-1a5b39f4b1d1" alt="Pre-Training" width="500"/>

Post-Training - Higher Probability of Betting (Green) for good hands, notice the diagonal axis having a higher probability of betting due to having a pair!

<img src="https://github.com/user-attachments/assets/8a73f886-818d-499f-9906-396a53a26ddc" alt="Post-Training" width="500"/>

![image]()
