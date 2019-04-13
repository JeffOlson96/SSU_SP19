import numpy as np
import matplotlib
import matplotlib.pyplot as plt

def main():


	#N = 500
	#x = np.random.rand(N)
	#y = np.random.rand(N)
	colors = (0,0,0)
	area = np.pi*3
	#x = [0,2,3]
	#y = [4,33,98]

	# task 1 generate 
	#
	#

	
	lst = []
	lst2 = []
	i = 0
	while(i < 10):
		lst.append(i*2)
		lst2.append(i)
		i+=1

 
# Plot
	plt.scatter(lst, lst2, s=area, c=colors, alpha=0.5)
	plt.title('Scatter plot')
	plt.xlabel('x')
	plt.ylabel('y')
	plt.show()

	return 0

main()
