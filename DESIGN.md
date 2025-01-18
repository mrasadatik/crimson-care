### Crimson Care System Design

---

### **General User Functionalities**

#### 1. **Buy Blood**

- Input the **hospital code** (a unique identifier for hospitals purchasing blood).
- Select the **blood group**.
- Enter the **desired quantity**.
- On successful purchase:
  - Record the transaction.
  - Display updated blood stock.

#### 2. **Sell Blood**

- Input the following details:
  - **Blood group**.
  - **Donor name**.
  - **Date of donation**.
- On successful entry:
  - Record the transaction.
  - Generate a "Thank You" note and a sell token.
  - **Note:** Blood stock will require manual update by the admin.

---

### **Admin Panel Functionalities**

#### 1. **Update Blood Quantity**

- Select the **blood group**.
- Input the **new quantity**.
- On success:
  - Update the stock in the JSON file.
  - Display a confirmation message.

#### 2. **Update Blood Price**

- Select the **blood group**.
- Input the **new price**.
- On success:
  - Update the price in the JSON file.
  - Display a confirmation message.

#### 3. **View Transactions**

- Display all transactions in a single, unified structure with the following details:
  - **Transaction ID**.
  - **Type** (`buy` or `sell`).
  - **Associated name**:
    - For `buy`: **hospital code**.
    - For `sell`: **donor name**.
  - **Blood group**.
  - **Quantity**.
  - **Date and time**.

#### 4. **Change Password**

- Allow the logged-in admin to update their password.
- Store the updated password securely in the `.dat` file.

#### 5. **Add Admin**

- Input:
  - **Name**.
  - **Username** (must be unique).
  - **Password**.
- On success:
  - Save the new admin credentials securely in the `.dat` file.

#### 6. **Add Hospital**

- Input:
  - **Hospital name**.
  - **Location**.
- On success:
  - Generate a unique **hospital code** using the hospital name.
  - Save the hospital details in the JSON file.

---

### **Transaction Structure**

All transactions are recorded in a single `transactions.json` file for consistency and simplicity.

#### Example Transaction Structure:

```json
[
  {
    "id": 1,
    "type": "buy",
    "entity": "HOSP001",
    "blood_group": "A+",
    "quantity": 5,
    "date_time": "2025-01-18 10:30:00"
  },
  {
    "id": 2,
    "type": "sell",
    "entity": "John Doe",
    "blood_group": "B+",
    "quantity": 3,
    "date_time": "2025-01-18 11:00:00"
  }
]
```

#### Fields:

- **`id`**: Auto-incremented unique identifier for the transaction.
- **`type`**: Specifies whether the transaction is a `buy` or `sell`.
- **`entity`**:
  - For `buy`: Contains the **hospital code**.
  - For `sell`: Contains the **donor name**.
- **`blood_group`**: Blood group involved in the transaction.
- **`quantity`**: Amount of blood purchased or donated.
- **`date_time`**: Timestamp of the transaction.

---

### **Data Storage and File Management**

1. **Blood Data** (`blood.json`):

   ```json
   {
     "A+": { "quantity": 50, "price": 200 },
     "B+": { "quantity": 30, "price": 250 }
   }
   ```

2. **Hospital Data** (`hospitals.json`):

   ```json
   [
     { "code": "CHD4587", "name": "City Hospital", "location": "Dhaka" },
     { "code": "GHC7984", "name": "General Hospital", "location": "Chittagong" }
   ]
   ```

3. **Admin Credentials** (`admins.dat`):
   - Admin credentials stored securely as serialized objects with hashed passwords.

---

### **System Rules and Constraints**

1. **Manual Stock Update for Sells**:

   - Blood stock changes after selling require manual updates by the admin.

2. **Unified Transaction Handling**:

   - All buy and sell transactions are stored in a single file, with clearly distinguished types (`buy` or `sell`).

3. **Auto-Increment IDs**:

   - Unique transaction IDs are generated sequentially.

4. **Unique Hospital Codes**:
   - Generated using hospital names and locations.
