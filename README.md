#TEST CASES:
product 1:
Monitor 1200 2
n
n
product 2:
Mouse 100 50
n
n
product 3:
GamingPC 10000 1
n
n
product 4:
GiftCard 200 5
n
n

product  5:
cheese 200 4
y
500
y
4/7/2025 5/7/2025

CUSTOMER:
ahmed
4000

test case 1(adding more than available stock): 1 3
test case 2(adding product with 0 quantity): 2 0
test case 3(insufficant balance): 3 1
test case 4(no error but no shipping and not expirable): 4 2
tes case 5 (expired): 5 2


#OOP C++
Product types: Shippable, Expirable
Features:
- Customer cart with balance checks
- 
- ShippingService output
- 
- Handles expired products, out-of-stock, and overspending

used inheritence, composition, encapsolaiton and abstraction

