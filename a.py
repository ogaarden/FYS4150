import matplotlib.pyplot as plt
import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.metrics import mean_squared_error


Xdata = x.flatten()

xtr, xte, ytr, yte = train_test_split(
    Xdata, y, test_size=0.3, random_state=50
)

degrees = range(1, 15)

mse_tr = []
mse_te = []

for degree in degrees:

    Xtr = np.vander(xtr, degree + 1, increasing=True)
    Xte = np.vander(xte, degree + 1, increasing=True)

    theta = np.linalg.lstsq(Xtr, ytr, rcond=None)[0]

    y_tr_pr = Xtr @ theta
    y_te_pr = Xte @ theta

    mse_tr.append(mean_squared_error(ytr, y_tr_pr))
    mse_te.append(mean_squared_error(yte, y_te_pr))


plt.plot(degrees, mse_tr, label="Training")
plt.plot(degrees, mse_te, label="Test")

plt.xlabel("Polynomial degree")
plt.ylabel("MSE")
plt.legend()
plt.show()

best_degree = degrees[np.argmin(mse_te)]

print("Best degree:", best_degree)
print("Minimum test MSE:", min(mse_te))