
import matplotlib.pyplot as plt
import pandas as pd
import os


def plot_error():
    # Les inn error-data
    df_error = pd.read_csv("data/rel_error100.csv")

    # Fjern eventuelle usynlige mellomrom i kolonnenavnene
    df_error.columns = df_error.columns.str.strip()

    # Opprett figur
    plt.figure()

    # Plot error
    plt.plot(
        df_error["X"],
        df_error["u"],
        label="Relativ feil"
    )

    plt.title("Relativ feil")
    plt.xlabel("X")
    plt.ylabel("Feil")
    plt.legend()
    plt.grid(True)

    plt.show()


import matplotlib.pyplot as plt
import pandas as pd
from pathlib import Path


def plot_numerical():

    path = Path("project1/data")

    # Eksakt løsning
    df_exact = pd.read_csv(path / "data_exact.csv")

    plt.figure()

    plt.plot(
        df_exact["X"],
        df_exact["u"],
        label="Eksakt løsning"
    )

    # Alle numeriske løsninger
    for file in path.glob("data_numerical*.csv"):

        df_num = pd.read_csv(file)

        plt.plot(
            df_num["X"],
            df_num["u"],
            label=file.stem
        )

    plt.title("Numerisk og eksakt løsning")
    plt.xlabel("X")
    plt.ylabel("u")
    plt.legend()
    plt.grid(True)

    plt.show()


def main():
    #plot_error()
    plot_numerical()


if __name__ == "__main__":
    main()

