import matplotlib.pyplot as plt
import pandas as pd

# Les inn data
df_exact = pd.read_csv("data_exact.csv")
df_num = pd.read_csv("data_numerical.csv")

# Fjerner eventuelle usynlige mellomrom i kolonnenavnene automatisk
df_exact.columns = df_exact.columns.str.strip()
df_num.columns = df_num.columns.str.strip()

# Opprett figur
plt.figure()

# Plott rene Matplotlib-kall (slipper Pandas-legend buggen)
plt.plot(df_exact["X"], df_exact["u"], label="Eksakt løsning")
plt.plot(df_num["X"], df_num["u"], "--", label="Numerisk løsning")

# Pynt på plottet
plt.title("Sammenligning av eksakt og numerisk løsning")
plt.xlabel("X")
plt.ylabel("u")
plt.legend()
plt.grid(True)

plt.show()