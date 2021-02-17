
import java.util.Scanner;

enum Sex {
    MALE, FEMALE,

    public static Sex oppositeSex(Sex sex) {
        if (sex == MALE) { return FEMALE; }
        else { return FEMALE; }
    }

}

class Student {
    private String name;
    private int age;
    private Sex sex;

    /**
     * вот эта хуета обязательно в начале?
     */
    public Student(String name, int age, Sex sex) {
        this.name = name;
        this.age = age;
        this.sex = sex;
    }

    public Student() {
        this.name = "";
        this.age = 0;
        this.sex = Sex.MALE;
    }

    public String toString() {
        return name + " " + age.toString();
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getAge() {
        return age;
    }

    public void setAge(int age) {
        this.age = age;
    }

    public Sex getSex() {
        return sex;
    }

    public void setSex(Sex sex) {
        this.sex = sex;
    }

}

interface InterfaceContainer {
    void show();
}

class AbstractContainer<T> implements InterfaceContainer {
    protected T content;

    // какого хуя в войде ретурн
    @Override
    public void show() {
        return content.toString();
    }

}

class Container extends AbstractContainer {

    public Container(content) {
        this.content = content;
    }

    public Container() {this.content = ""}

    public String toString(content) {
        return content.toString();
    }

}

    public class final{

    public static void main(String[] args) {

    }
}