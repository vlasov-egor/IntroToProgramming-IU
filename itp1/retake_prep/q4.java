import java.util.*;

// чекни 1 задание в 4 чекнул.  там надо абстракт ебануть. есть идея куда? нэт

// Типа есть разные типы транзакций, возврат покупка бла бла бла

public class q4 {
    public static void main(String[] args) {
        Product ps5 = new Product("PS5", "Gaming console", 99.0);
        ps5.setCurrentUnitPrice(999F);
        
        Product xbox = new Product("Xbox", "Gaming console", 34.0);
        xbox.setCurrentUnitPrice(676F);

        Address address = new Address("Universitetskaya 1", "Rushka");
        Person owner = new Person("Egor", "Vlasov", address);
        Account account = new Account("Hello World", owner);

        Transaction psTransaction = new BuyTransaction(10.0, new Date(), ps5);
        Transaction xboxTransaction = new BuyTransaction(11.0, new Date(), xbox);

        account.addTransaction(psTransaction);
        account.addTransaction(xboxTransaction);

        System.out.println(account.accountTotal());
    }
}

abstract class Transaction {
    protected Double unit; // НАПИШИ ЧТО ОНО ДОЛЖНО БЫТЬ ПРОТЕКТЕД ИЗ-ЗА АБСТРАКТА
    protected Date transactionDate;
    protected Product product;

    public Product getProduct () {
        return this.product;
    }
}

class BuyTransaction extends Transaction {
    public BuyTransaction(Double unit, Date transactionDate, Product product) {
        this.unit = unit;
        this.transactionDate = transactionDate;
        this.product = product;
    }
}

interface Loan {
    public Float getLoanInterest();
    public Set<Person> getLenders();
    public void setLoanInterest(Float value);
    public void setLenders(Set<Person> value);
}

interface ManagedFund {
    public String getFundId();
    public Float getCurrentUnitPrice();
    public void setFundId(String value);
    public void setCurrentUnitPrice(Float value);
}

interface Cash {
    public Float getCashInterest();
    public void setCashInterest(Float value);
}

class Product implements Loan, ManagedFund, Cash {
    private String name;
    private String description;
    private Double managementFee;

    private Float loanInterest;
    private Set<Person> lenders;
    
    private String fundId;
    private Float currentUnitPrice;
    
    private Float cashInterest;

    public Product(String name, String description, Double managemntFee) {
        this.name = name;
        this.description = description;
        this.managementFee = managemntFee;
    }

    @Override
    public Float getCashInterest() {
        // TODO Auto-generated method stub
        return null;
    }

    @Override
    public void setCashInterest(Float value) {
        // TODO Auto-generated method stub
    }

    @Override
    public String getFundId() {
        // TODO Auto-generated method stub
        return null;
    }

    @Override
    public Float getCurrentUnitPrice() {
        return this.currentUnitPrice;
    }

    @Override
    public void setFundId(String value) {
        // TODO Auto-generated method stub
    }

    @Override
    public void setCurrentUnitPrice(Float value) {
        this.currentUnitPrice = value;
    }

    @Override
    public Float getLoanInterest() {
        // TODO Auto-generated method stub
        return null;
    }

    @Override
    public Set<Person> getLenders() {
        // TODO Auto-generated method stub
        return null;
    }

    @Override
    public void setLoanInterest(Float value) {
        // TODO Auto-generated method stub
    }

    @Override
    public void setLenders(Set<Person> value) {
        // TODO Auto-generated method stub
    }
}

class Account {
    private String name;
    private Set<Person> owners;
    private Person manager;
    private List<Transaction> trasactions = new ArrayList<Transaction>();

    public Account (String name, Person owner) {
        this.name = name;
        this.owners = new HashSet<>(Arrays.asList(owner));
    }

    public Account (String name, Set<Person> owners, Person manager) {
        this.name = name;
        this.owners = owners;
        this.manager = manager;
    }

    public void addTransaction(Transaction newTransaction) {
        trasactions.add(newTransaction);
    }

    public Float accountTotal() {
        Float total = 0F;

        for (Transaction transaction : trasactions) {
            total += transaction.getProduct().getCurrentUnitPrice(); 
        }

        return total;
    }
}

class Person {
    private String firstName;
    private String lastName;
    private Address address;

    public Person(String firstName, String lastName, Address address) {
        this.firstName = firstName;
        this.lastName = lastName;
        this.address = address;
    }

    public String getFirstName () {
        // TODO Auto-generated method stub
        return null;
    }

    public String getLastName () {
        // TODO Auto-generated method stub
        return null;
    }

    public Address getAddress () {
        // TODO Auto-generated method stub
        return null;
    }
}

class Address {
    private String streetName;
    private String country;

    public Address(String streetName, String country) {
        this.streetName = streetName;
        this.country = country;
    }

    public String getStreetName() {
        // TODO Auto-generated method stub
        return null;
    }

    public String getCountry() {
        // TODO Auto-generated method stub
        return null;
    }
}