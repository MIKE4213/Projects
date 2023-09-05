import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
sns.set()
from sklearn.cluster import KMeans

s_data = pd.read_csv('Data points cluster states.csv')
print(s_data)

plt.scatter(s_data['longitude'], s_data['latitude'])
plt.xlim(-160,-50)
plt.ylim(0, 70)
plt.show()

#means = np.array([[33, -85], [36, -115], [42, -92]])

x = s_data.iloc[:,1:3]
print(x)

kmeans = KMeans(4)
#kmeans.fit(means)

clusters = kmeans.fit_predict(x)
data_with_clusters = s_data.copy()

data_with_clusters['Clusters'] = clusters
print(data_with_clusters)

plt.scatter(data_with_clusters['longitude'], data_with_clusters['latitude'], c=clusters, cmap='Set1')
plt.xlim(-160, -50)
plt.ylim(0, 70)
plt.show()