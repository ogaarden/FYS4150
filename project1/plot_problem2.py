import pandas as pd
import matplotlib.pyplot as plt


df = pd.read_csv("data/analytical_solution.csv",skiprows=1,  names = ["x", "u"])

plt.figure(figsize=(8, 5))
plt.plot(df["x"], df["u"], color="blue", linewidth=2, label="Analytisk")

# Vanlig Matplotlib-pynting:
plt.title("Analytisk løsning")
plt.xlabel("x-verdi")
plt.ylabel("u(x)")
plt.grid(True)
plt.legend()

plt.show()

