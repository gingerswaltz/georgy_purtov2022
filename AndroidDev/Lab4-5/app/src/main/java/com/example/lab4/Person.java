package com.example.lab4;

public class Person {
    private String name;
    private String phoneNumber;
    private String email;
    private String address;
    private String hexcolor;

    private boolean isLastItem;

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getPhoneNumber() {
        return phoneNumber;
    }

    public void setPhoneNumber(String phoneNumber) {
        this.phoneNumber = phoneNumber;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public String getAddress() {
        return address;
    }

    public void setAddress(String address) {
        this.address = address;
    }

    public String getHexColor() {
        return hexcolor;
    }

    public void setHexColor(String hexcolor) {
        this.hexcolor = hexcolor;
    }

    public boolean isLastItem() {
        return isLastItem;
    }

    public void setLastItem(boolean lastItem) {
        isLastItem = lastItem;
    }
}