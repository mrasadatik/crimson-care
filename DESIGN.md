### Crimson Care System Design

This system is designed to manage blood transactions efficiently, with distinct functionalities for general users and administrators. Data is stored in JSON files for easy management, while sensitive admin credentials are securely stored in a `.dat` file or another secure format.

---

### **General User Functionalities**

#### 1. **Buy Blood**

- Input the **hospital code** (a unique identifier for hospitals purchasing blood).
- Select the **blood group**.
- Enter the **desired quantity**.
- On successful purchase:
  - Display a success message.
  - Show the updated blood stock.

#### 2. **Sell Blood**

- Input the following details:
  - **Blood group**.
  - **Donor name**.
  - **Date of donation**.
- On successful entry:
  - Generate a "Thank You" note.
  - Provide a **sell token**.
  - **Note:** The blood stock will not update automatically; it will require admin input.

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

- Display a list of all transactions (buy/sell) with details:
  - **Transaction ID**.
  - **Type** (buy/sell).
  - **Blood group**.
  - **Quantity**.
  - **Associated hospital code** or donor name.
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

### **Data Storage and File Management**

1. **Blood Data** (`blood.json`):

   ```json
   {
     "A+": { "quantity": 50, "price": 200 },
     "B+": { "quantity": 30, "price": 250 }
   }
   ```

2. **Transactions** (`transactions.json`):

   ```json
   [
     {
       "id": 1,
       "type": "buy",
       "hospital_code": "HOSP001",
       "blood_group": "A+",
       "quantity": 5,
       "date_time": "2025-01-18 10:30:00"
     },
     {
       "id": 2,
       "type": "sell",
       "donor_name": "John Doe",
       "blood_group": "B+",
       "date_time": "2025-01-18 11:00:00"
     }
   ]
   ```

3. **Hospital Data** (`hospitals.json`):

   ```json
   [
     { "code": "CHD4578", "name": "City Hospital", "location": "Dhaka" },
     { "code": "GHC8749", "name": "General Hospital", "location": "Chittagong" }
   ]
   ```

4. **Admin Credentials** (`admins.dat`):
   - Admin credentials are stored as serialized objects with hashed passwords for security.

---

### **System Rules and Constraints**

1. **Manual Stock Update**:

   - Blood stock changes after selling require manual updates by the admin.

2. **Auto-Increment IDs**:

   - Transaction IDs are generated sequentially to ensure uniqueness.

3. **Unique Hospital Codes**:
   - Hospital codes are generated based on the hospital name and location, ensuring uniqueness (e.g., prefix system).

---

### **Additional Features**

- **Error Handling**:
  - Input validation for quantities and unique identifiers (e.g., hospital codes, usernames).
- **Logging**:
  - Maintain logs for failed or suspicious transactions for fraud prevention.
