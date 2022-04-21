# Collectible-Store
Store data structure that tracks input 'Collectible' objects and maintains a register of objects, customers, and transactions.

Collectibles are implemented using object-oriented design methods.
There are three types of items that can be recorded in the Store:
• Coins
• Comic books
• Sports Cards

Customer transactions (buy/sell) are also recorded as part of store history. These transaction types are:
• Sell: removes an item from the store inventory
• Buy: adds an item to the store inventory
• Display: outputs the entire inventory of the store, including the number of each item in inventory
• Customer: outputs all of the transactions for a customer (in chronological order), including the item
• History: outputs the history for every customer, with the customers in alphabetical order.

Collectibles are stored using a binary search tree, while customers are hashed into an array by their unique customer ID.
