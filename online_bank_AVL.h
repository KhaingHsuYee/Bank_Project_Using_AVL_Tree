//
// Created by Khaing Hsu Yee on 5/29/2023.
//

#ifndef BANK_PROJECT_USING_AVL_TREE_ONLINE_BANK_AVL_H
#define BANK_PROJECT_USING_AVL_TREE_ONLINE_BANK_AVL_H

#endif //BANK_PROJECT_USING_AVL_TREE_ONLINE_BANK_AVL_H
#include "stdio.h"
#include "stdlib.h"
#include "time.h"

struct trans{
    char note[200];
    char withdrawRecord[200];
    char loanRecord[200];
    char cashInRecord[200];
    char updateRecord[200];
};
struct data{
     int id;
    char name[30];
    char nrc[50];
    char email[50];
    char password[50];
    char pOrb[20];
    char loan_s[2];
    unsigned int monthly_income;
    unsigned int loan_amount;
    float loan_rate;
    char acc_s[10];
    int acc_level;
    unsigned int phNumber;
    unsigned int cur_amount;
    char address[100];
    int transAmoLimitPerDay;
    int noOfTransferRecord;
    int noOfWithdrawalRecord;
    int noOfCashInRecord;
    int noOfLoanRecord;
    int noOfUpdateRecord;

    struct trans trc[100];

};
struct node
{

    struct data info;

    struct node* left;
    struct node* right;
    int ht;
};

struct my_time{
    char c_time[25];
};
// global initialization of db_root
// node
struct node* db_root
        = NULL;
//int users=0;

int emailExist=-1;
int idExist = -1;
int phExist =-1;
int two_charArray=-1;
int strongPass = -1;
int gValid = -1;
int ph_found = -1;
struct data temp;
struct data receiverInfo;
struct my_time Ctime[1];
int last_id;
unsigned int charArray_to_unsignedInt_data=0;
char int_to_char_array_data[10];
unsigned int current_day_toTransfer = 0;
int trans_limit =0;


struct node* create(struct data);
struct node* insert(struct node*, struct data);
struct node* rotate_left(struct node*);
struct node* rotate_right(struct node*);
int balance_factor(struct node*);
int height(struct node*);
void loadingAllDataFromFile();
void printing_one_person_data(struct node* root);
void printingalldata();
void recording_alldata_toFile();
void recording_oneperson_data_toFile(FILE *fptr, struct node *root);
void welcome();
void login();
void userSector();
int charCounting(char toCount[100]);
void id_Checking(struct node * root
        ,int toCheck);
void emailExistChecking(struct node* root
        ,char toCheck[50]);
void compare_two_charArray(char first[50],char second[50]);
void myStrongPassword(char pass[50]);
void myGmailValidation(char toValidate[50]);
void getLastBiggestId(struct node* root
        );
void copy_two_char_array(char receiver[50],char transmiter[50]);

void finding_phone_number(struct node*root
        ,unsigned int toFind);
void registration();
void getTime();
void current_data_toTransfer();
unsigned int calculate_amounts_same_days();
void get_limit_amount();
void copy_struct_to_tree(struct node* root
        ,struct data newInfo);
void transaction_record(char who,unsigned int amount);
void transaction_record_for_withdrawal(unsigned int amount);
void update_information_record(char type);
void cashIn_record(unsigned int amount);
void charArray_to_unsigned_fun(char charArray[]);
void integer_to_char(unsigned int value);
void phone_validation(struct node *root  , unsigned int ph_no);
void transfer_money(unsigned int amount);
void withdraw_money();
void update_information();
void cashIn();
void view_history();
int check_input(char input[2]);
struct node* create(struct data info1)
{
    struct node* new_node = (struct node*) malloc (sizeof(struct node));

    // if a memory error has occurred
    if (new_node == NULL)
    {
        printf("\nMemory can't be allocated\n");
        return NULL;
    }

    new_node->info = info1;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

// rotates to the left
struct node* rotate_left(struct node* root )
{
    struct node* right_child = root->right;
    root->right = right_child->left;
    right_child->left = root ;

    // update the heights of the nodes
    root->ht = height(root );
    right_child->ht = height(right_child);

    // return the new node after rotation
    return right_child;
}

// rotates to the right
struct node* rotate_right(struct node* root  )
{
    struct node* left_child = root->left;
    root->left = left_child->right;
    left_child->right = root;

    // update the heights of the nodes
    root->ht = height(root );
    left_child->ht = height(left_child);

    // return the new node after rotation
    return left_child;
}

// calculates the balance factor of a node
int balance_factor(struct node* root )
{
    int lh, rh;
    if (root == NULL)
        return 0;
    if (root->left == NULL)
        lh = 0;
    else
        lh = 1 + root->left->ht;
    if (root->right == NULL)
        rh = 0;
    else
        rh = 1 + root->right->ht;
    return lh - rh;
}

// calculate the height of the node
int height(struct node* root )
{
    int lh, rh;
    if (root == NULL)
    {
        return 0;
    }
    if (root->left == NULL)
        lh = 0;
    else
        lh = 1 + root->left->ht;
    if (root->right == NULL)
        rh = 0;
    else
        rh = 1 + root->right->ht;

    if (lh > rh)
        return (lh);
    return (rh);
}

// inserts a new node in the AVL tree
struct node* insert(struct node* root
        , struct data info1)
{
    if (root == NULL)
    {
        struct node* new_node = create(info1);
        if (new_node == NULL)
        {
            return NULL;
        }
        root = new_node;
    }
    else if (info1.id > root->info.id)
    {
        // insert the new node to the right
        root->right = insert(root->right, info1);

        // tree is unbalanced, then rotate it
        if (balance_factor(root) == -2)
        {
            if (info1.id > root->right->info.id)
            {
                root  = rotate_left(root );
            }
            else
            {
                root->right = rotate_right(root->right);
                root = rotate_left(root );
            }
        }
    }
    else
    {
        // insert the new node to the left
        root->left = insert(root->left, info1);

        // tree is unbalanced, then rotate it
        if (balance_factor(root) == 2)
        {
            if (info1.id < root->left->info.id)
            {
                root  = rotate_right(root );
            }
            else
            {
                root->left = rotate_left(root->left);
                root   = rotate_right(root );
            }
        }
    }
    // update the heights of the nodes
    root->ht = height(root);
    return root
    ;
}
void loadingAllDataFromFile() {

    FILE *fptr= fopen("ncc_db2.txt","r");
    if(fptr==NULL){
        printf("Error at loadingAllDataFromFile Function!\n");
    }
    else{
        while(!feof(fptr)){
            struct data info1;
            fscanf(fptr,"%u%s%s%s%s%s%s%u%u%f%s%d%u%u%s%d%d%d%d%d%d",&info1.id,&info1.name,&info1.nrc,
                   &info1.email,&info1.password,&info1.pOrb,&info1.loan_s,&info1.monthly_income,
                   &info1.loan_amount,&info1.loan_rate,&info1.acc_s,&info1.acc_level,&info1.phNumber,
                   &info1.cur_amount,&info1.address,&info1.transAmoLimitPerDay,&info1.noOfTransferRecord,
                   &info1.noOfWithdrawalRecord,
                   &info1.noOfCashInRecord,&info1.noOfLoanRecord,&info1.noOfUpdateRecord);
//            int indexPoint =0 ;

            for(int gcc=0;gcc<info1.noOfTransferRecord;gcc++){
                fscanf(fptr," %s",&info1.trc[gcc].note[0]);
//                indexPoint++;
            }
            for(int gcc=0;gcc<info1.noOfWithdrawalRecord;gcc++){
                fscanf(fptr," %s",&info1.trc[gcc].withdrawRecord[0]);
//                indexPoint++;
            }
            for(int gcc=0;gcc<info1.noOfCashInRecord;gcc++){
                fscanf(fptr," %s",&info1.trc[gcc].cashInRecord[0]);
//                indexPoint++;
            }
            for(int gcc=0;gcc<info1.noOfLoanRecord;gcc++){
                fscanf(fptr," %s",&info1.trc[gcc].loanRecord[0]);
//                indexPoint++;
            }
            for(int gcc=0;gcc<info1.noOfUpdateRecord;gcc++){
                fscanf(fptr," %s",&info1.trc[gcc].updateRecord[0]);
//                indexPoint++;
            }


            db_root = insert(db_root ,info1);





        }
        fclose(fptr);
    }

}
void printingalldata(){
    printing_one_person_data(db_root);
}
void printing_one_person_data(struct node* root
        )
{
    if (root == NULL)
    {
        return;
    }

    printing_one_person_data(root->left);

        printf("%u-%s-%s-%s-%s-%s-%s-%u-%u-%f-%s-%d-%u-%u-%s-%d-%d-%d-%d-%d-%d", root->info.id, root ->info.name,
               root->info.nrc, root->info.email, root->info.password, root->info.pOrb, root ->info.loan_s, root ->info.monthly_income,
               root ->info.loan_amount, root ->info.loan_rate, root->info.acc_s, root->info.acc_level, root ->info.phNumber,
               root ->info.cur_amount, root ->info.address, root->info.transAmoLimitPerDay, root ->info.noOfTransferRecord,
               root ->info.noOfWithdrawalRecord,  root ->info.noOfCashInRecord, root->info.noOfLoanRecord, root->info.noOfUpdateRecord);
        int indexPoint=0;
        for(int gcc=0; gcc < root->info.noOfTransferRecord;gcc++){
            printf("-%s",&root->info.trc[gcc].note[0]);
            indexPoint++;
        }
        for(int wcc=0; wcc < root->info.noOfWithdrawalRecord;wcc++){
            printf("-%s",&root->info.trc[wcc].withdrawRecord[0]);
            indexPoint++;
        }
        for(int wcc=0; wcc < root->info.noOfCashInRecord;wcc++){
            printf("-%s",&root->info.trc[wcc].cashInRecord[0]);
            indexPoint++;
        }
        for(int wcc=0; wcc < root->info.noOfLoanRecord;wcc++){
            printf("-%s",&root->info.trc[wcc].loanRecord[0]);
            indexPoint++;
        }
        for(int wcc=0; wcc < root->info.noOfUpdateRecord;wcc++){
            printf("-%s",&root->info.trc[wcc].updateRecord[0]);
            indexPoint++;
        }
        printf("\n");


    printing_one_person_data(root->right);
}

void recording_alldata_toFile() {

    FILE *fptr = fopen("ncc_db2.txt", "w");
    if (fptr == NULL) {
        printf("cannot open file to record:\n");
    } else {
        getLastBiggestId(db_root);
        recording_oneperson_data_toFile(fptr,db_root );

    }
}

void recording_oneperson_data_toFile(FILE *fptr, struct node *root ) {

    if(root == NULL){
        return;
    }
    recording_oneperson_data_toFile(fptr, root->left);
    fprintf(fptr,"%u%c%s%c%s%c%s%c%s%c%s%c%s%c%u%c%u%c%f%c%s%c%d%c%u%c%u%c%s%c%d%c%d%c%d"
                 "%c%d%c%d%c%d",
            root ->info.id, ' ', root ->info.name, ' ', root->info.nrc, ' ',   root ->info.email, ' ',
            root ->info.password, ' ', root->info.pOrb, ' ', root->info.loan_s, ' ', root->info.monthly_income, ' ',
            root ->info.loan_amount, ' ', root->info.loan_rate, ' ', root->info.acc_s, ' ',
            root ->info.acc_level, ' ', root->info.phNumber, ' ', root->info.cur_amount, ' ', root->info.address, ' ',
            root ->info.transAmoLimitPerDay,' ', root->info.noOfTransferRecord, ' ', root->info.noOfWithdrawalRecord, ' ',
            root ->info.noOfCashInRecord, ' ', root->info.noOfLoanRecord, ' ', root->info.noOfUpdateRecord);

    for(int gcc=0; gcc < root->info.noOfTransferRecord;gcc++){
        fprintf(fptr, " %s", root->info.trc[gcc].note);

    }
    for(int gcc=0; gcc < root->info.noOfWithdrawalRecord;gcc++){
        fprintf(fptr, " %s", root ->info.trc[gcc].withdrawRecord);

    }
    for(int gcc=0; gcc < root->info.noOfCashInRecord;gcc++){
        fprintf(fptr, " %s", root->info.trc[gcc].cashInRecord);

    }
    for(int gcc=0; gcc < root->info.noOfLoanRecord;gcc++){
        fprintf(fptr, " %s", root->info.trc[gcc].loanRecord);

    }
    for(int gcc=0; gcc < root->info.noOfUpdateRecord;gcc++){
        fprintf(fptr, " %s", root->info.trc[gcc].updateRecord);

    }

    if(last_id != root->info.id){
        fprintf(fptr,"%c",'\n');
    }

    recording_oneperson_data_toFile(fptr, root->right);

}

void welcome() {

    char input[2];

    int option = 0;
    printf("Press 1 to login:\nPress 2 to register:\nPress 3 to exit:");
    scanf(" %[^\n]",&input[0]);
    option = check_input(input);
    if(option == 49){
        login();
    }
    else if(option == 50){
        registration();
    }
    else if(option == 51){
        recording_alldata_toFile();
        printf("Good Bye!Have a good day!");
        exit(1);
    }else{
        printf("Invalid option\n");
        welcome();
    }

}

void registration() {

    char reEmail[50] = "\0";
    char reName[50] = "\0";
    char reNrc[50] = "\0";
    char repassword[50] = "\0";
    unsigned int rephNo=0;
    struct data reg_info;
    char reAcc_s[10] = {'n','e','w'};
    char reLoan_s[2]={'T'};

    printf("This is NCC Bank User Registration!\n");
    printf("Enter your email:");
    scanf(" %[^\n]",&reEmail[0]);
    emailExist = -1;
    emailExistChecking(db_root
                       ,reEmail);
    if(emailExist == -1){
        gValid = -1;
        myGmailValidation(reEmail);
        if(gValid != -1){
//            printf("Your gmail format is correct!\n");
            printf("Enter your name:");
            scanf(" %[^\n]",&reName[0]);
            printf("Enter your NRC:");
            scanf(" %[^\n]",&reNrc[0]);
            strongPass=-1;
            while (strongPass==-1){
                printf("Enter your password:");
                scanf(" %[^\n]",&repassword[0]);
                myStrongPassword(repassword);
                if(strongPass==-1){
                    printf("Your password is weak and easy to guess!\n");
                }
            }
            printf("Your password is valid and saved!\n");

            do{
                printf("Enter your phone number:");
                scanf("%u",&rephNo);
                phExist = -1;
                phone_validation(db_root
                                 ,rephNo);
                if(phExist!=-1){
                    printf("Your phone number is already taken!\n");
                }

            }while (phExist!=-1);
            printf("Your phone number is valid and saved!\n");
            getLastBiggestId(db_root
            );
            reg_info.id = last_id+1;
            copy_two_char_array(reg_info.email,reEmail);
            copy_two_char_array(reg_info.name,reName);
            copy_two_char_array(reg_info.password,repassword);
            copy_two_char_array(reg_info.nrc,reNrc);
            reg_info.phNumber = rephNo;
            printf("Enter your monthly income:");
            scanf("%u",&reg_info.monthly_income);
            printf("Enter your current amount:");
            scanf("%u",&reg_info.cur_amount);
            printf("Enter your address:");
            scanf(" %[^\n]",&reg_info.address[0]);
            reg_info.loan_amount = 1000;
            reg_info.loan_rate = 0.3;
            copy_two_char_array(reg_info.loan_s,reLoan_s);

            copy_two_char_array(reg_info.acc_s,reAcc_s);
            reg_info.acc_level = 3;
            int optionValid = -1;
            char option;
            while(optionValid == -1){
                printf("Press 'P' for making personal account and Press 'B' for making business account:");
                scanf(" %c",&option);
                if(option == 'P'){
                    char rePorB[20]={'p','e','r','s','o','n','a','l'};
                    copy_two_char_array(reg_info.pOrb,rePorB);
                    optionValid = 1;
                }
                else if(option == 'B'){
                    char rePorB[20]={'b','u','s','i','n','e','s','s'};
                    copy_two_char_array(reg_info.pOrb,rePorB);
                    optionValid = 1;
                }
                else{
                    printf("Invalid Option!\n");
                }
            }
            reg_info.transAmoLimitPerDay = 10000;
            reg_info.noOfTransferRecord = 0;
            reg_info.noOfWithdrawalRecord = 0;
            reg_info.noOfCashInRecord = 0;
            reg_info.noOfUpdateRecord =0 ;
            reg_info.noOfLoanRecord = 0;

            db_root
            = insert(db_root
                    ,reg_info);
            printf("Registrated Successfully!\n");
            printf("Your id is %d",reg_info.id);
            printf("\nUse this id whenever you login your account\n");
            printingalldata();
            welcome();



        }
        else{
            printf("Your gmail format is incorrect!\n");
            registration();
        }
    }
    else{
        printf("Your email already exists!\n");
        registration();
    }

}

void phone_validation(struct node *root
        , unsigned int ph_no) {

    if(phExist == -1){
        if(root == NULL){
            return;
        }
        phone_validation(root->left, ph_no);
        if(ph_no == root->info.phNumber){
            phExist = 1;
        }
        phone_validation(root ->right, ph_no);
    }

}

void login(){

    char L_email[50];
    char L_pass[50];
    int L_id=0;
    emailExist=-1;
    two_charArray=-1;
    idExist=-1;

    while(idExist == -1 || two_charArray == -1){
        printf("This is Login!\n");
        printf("Enter your id:");
        scanf("%d",&L_id);
        printf("Enter your email:");
        scanf(" %[^\n]",&L_email[0]);
        printf("Enter your password:");
        scanf(" %[^\n]",&L_pass[0]);
        idExist=-1;
        id_Checking(db_root ,L_id);
        if(idExist != -1){
            two_charArray = -1;
            compare_two_charArray(L_email,temp.email);
            if(two_charArray != -1){

                two_charArray = -1;
                compare_two_charArray(L_pass,temp.password);
                if(two_charArray == -1){



                    printf("Your login credential was wrong:\n");
                }
                else{
                    break;
                }
            }
            else{
                printf("Your email was wrong!\n");
            }
        }
        else{
            printf("Your id was wrong:\n");
        }


    }
    printf("Welcome Mr/Mrs %s",temp.name);
    printf("\nYour current amount is %u\n",temp.cur_amount);
    userSector();

}

void userSector() {



    char input[2];
    int user_option=0;
    unsigned int phone=0;
    unsigned  int amount_to_transfer=0;
    printf("\nThis is user sector\n");
    printf("Press 1 to Transfer Money:\nPress 2 to Withdraw:"
           "\nPress 3 to update your information\nPress 4 Cash in :"
           "\nPress 5 to view your history:\nPress 6 Exit:");
    scanf(" %[^\n]",&input[0]);
    user_option = check_input(input);
    if(user_option == 49) {
        printf("This is for Transfer Option:\n");
        ph_found=-1;
        while(ph_found == -1){
            printf("Enter receiver 's phone number:");
            scanf("%u",&phone);
            finding_phone_number(db_root
                                 ,phone);
            if(ph_found == -1){
                printf("Your receiver phone number does not belong to any user!\n");
            }
        }
        printf("Are you sure to transfer to %s with email : %s\n",receiverInfo.name,
               receiverInfo.email);
        while(amount_to_transfer<temp.cur_amount){
            printf("Enter the amount to transfer:");
            scanf("%u",&amount_to_transfer);
            if(amount_to_transfer<temp.cur_amount-1000){
                break;

            }else{
                printf("Your balance is not enough to transfer!\n");
                amount_to_transfer=0;
            }
        }
        two_charArray = -1;
        char trans_pass[50];
        int wrong_count=0;
        while (two_charArray == -1){
            printf("Enter your password to proceed transaction:");
            scanf(" %[^\n]",&trans_pass[0]);
            compare_two_charArray(temp.password,trans_pass);
            if(two_charArray == -1){
                printf("Wrong Password!\n");
                wrong_count++;
            }
            if(wrong_count == 3){
                printf("Wrong Password for three times.\nSo you need to wait for some time!\n");
                userSector();
            }
        }
        transfer_money(amount_to_transfer);
//        calculate_amounts_same_days();

    }
    else if(user_option==50) {
        printf("This is  withdraw sector!\n");
        withdraw_money();
    }
    else if(user_option==51) {
        update_information();
    }
    else if(user_option==52){
        cashIn();
    }
    else if(user_option==53){
        view_history();
    }
    else if(user_option==54){

        welcome();

    }
    else{
        printf("Invalid option!");
        userSector();
    }



}

int charCounting(char toCount[100]){
    int count=0;
    for(int gcc=0;gcc<100;gcc++){
        if(toCount[gcc] == '\0'){
            break;
        }
        else
            count++;
    }
    return count;
}
void emailExistChecking(struct node* root ,char toCheck[50]){
    if(emailExist == -1){
        if (root  == NULL) {
            return;
        }

        emailExistChecking(root->left, toCheck);
        int toCheckCount= charCounting(toCheck);
        int sameCount = 0;

        int dbEmailCount= charCounting(root->info.email);
        sameCount=0;
        if(toCheckCount==dbEmailCount){
            for(int i=0;i<toCheckCount;i++){
                if(toCheck[i] != root->info.email[i])
                    break;
                else
                    sameCount++;
            }
        }

        if(sameCount==toCheckCount){
//            temp = root
//            ->info;
            emailExist=root ->info.id;

        }

        emailExistChecking(root->right, toCheck);
    }




}
void id_Checking(struct node * root ,int toCheck){
    if(root == NULL){
        return;
    }
    if(root->info.id == toCheck){
        temp = root->info;
        idExist = root->info.id;
    }
    else if(root->info.id > toCheck){
        id_Checking(root->left, toCheck);
    }else{
        id_Checking(root->right, toCheck);
    }

}
void compare_two_charArray(char first[50],char second[50]){
    int firstCount= charCounting(first);
    int secondCount= charCounting(second);
    int sameCount=0;
    if(firstCount==secondCount){
        for(register int i=0;i<firstCount;i++){
            if(first[i] != second[i]){
                break;
            }
            else{
                sameCount++;
            }
        }
        if(firstCount==sameCount){
            two_charArray=1;
        }
    }
}
void myStrongPassword(char pass[50]){
    int pass_counter= charCounting(pass);
    int i=0;
    int special=0;
    int numchar=0;
    int capChar=0;
    int smallChar=0;
    while(strongPass==-1){
        if(i==pass_counter){
            strongPass=-1;
            break;
        }
        if(pass[i] >= 33 && pass[i] <= 42){
            special++;
        }
        else if(pass[i] >= 48 && pass[i] <= 57){
            numchar++;
        }
        else if(pass[i] >= 65 && pass[i] <= 90){
            capChar++;
        }
        else if(pass[i] >= 97 && pass[i] <= 122){
            smallChar++;
        }
        i++;
        if(special > 0 && numchar >0 && capChar >0 && smallChar >0){
            strongPass=1;
        }

    }

}
void myGmailValidation(char toValidate[50]){
    int endPoint= charCounting(toValidate);
    char form[10]={'@','g','m','a','i','l','.','c','o','m'};
    int count=0;
    for(int i=0;i<endPoint;i++){
        if(toValidate[i] == '@' || toValidate[i]== ' '){
            break;
        } else{
            count++;
        }
    }
    int toCheck=0;
    for(int i=0;i<endPoint;i++){
        if(toValidate[count] != form[i])
            break;
        else{
            count++;
            toCheck++;
        }
    }
    if(toCheck == 10){
        gValid=1;
    }
}
void getLastBiggestId(struct node* root ){
    if (root == NULL){
        return;
    }
    getLastBiggestId(root->left);
    last_id = root ->info.id;
    getLastBiggestId(root->right);
}
void copy_two_char_array(char receiver[50],char transmiter[50]){
    int transmitter_count= charCounting(transmiter);
    int receiver_count = charCounting(receiver);
    for(int i=0;i<transmitter_count;i++){
        receiver[i]=transmiter[i];
    }
    if(receiver[transmitter_count] != '\0'){
        receiver[transmitter_count] = '\0';
    }



}

void finding_phone_number(struct node* root ,unsigned int toFind){

    if(root == NULL){
        return;
    }
    finding_phone_number(root->left, toFind);
    if(root->info.phNumber == toFind){
        receiverInfo = root ->info;
        ph_found = root ->info.id;
    }
    finding_phone_number(root ->right, toFind);


}
void getTime(){
    time_t tm;
    time(&tm);

//    printf("Current time =%s\n ", ctime(&tm));

    FILE *fptr = fopen("myTime.txt","w");

    fprintf(fptr,"%s", ctime(&tm));
    fclose(fptr);

    int index=0;
    int time_space_counter = 0;


    Ctime[0].c_time[index]='-';
    index++;


    FILE *fptr2 = fopen("myTime.txt","r");
    char c = fgetc(fptr2);

    while(!feof(fptr2)){
        if( c == ' '){
            time_space_counter++;
            if(time_space_counter == 1){
                Ctime[0].c_time[index] ='!';
                c= fgetc(fptr2);
                index++;
            }
            else if(time_space_counter == 4){
                Ctime[0].c_time[index] ='@';
                c = fgetc(fptr2);
                index++;
            }
            else{
                Ctime[0].c_time[index] ='-';
                c = fgetc(fptr2);
                index++;
            }
        }else{
            Ctime[0].c_time[index]=c;
            c = fgetc(fptr2);
            index++;
        }
    }
}
void current_data_toTransfer(){
    char get_current_day[2];

    getTime();


    get_current_day[0]= Ctime[0].c_time[9];
    get_current_day[1]= Ctime[0].c_time[10];
    charArray_to_unsigned_fun(get_current_day);
    printf("\nCurrent day : %d\n",charArray_to_unsignedInt_data);

//    current_amount_toTransfer = current_amount_toTransfer;
    current_day_toTransfer = charArray_to_unsignedInt_data;
}
unsigned int calculate_amounts_same_days(){
    current_data_toTransfer();
    unsigned int total_amount_for_same_day = 0;
    int record_counter=temp.noOfTransferRecord;
    int index_counter = 0;
    char amount_char_array[10];
    char day_char_array[3];
    for(int a=record_counter-1;a>0;a--){
        int current_record_counter = charCounting(temp.trc[a].note);

        for(int aa=0;aa<current_record_counter;aa++){
            if(temp.trc[a].note[aa] == '$'){
                break;
            }
            index_counter++;
        }
        int quantity_of_amount = 0;
        for(int aaa=index_counter;aaa<current_record_counter;aaa++){
            if(temp.trc[a].note[aaa]=='-'){
                break;
            }
            quantity_of_amount++;
//            index_counter++;
        }
        index_counter++;
        for(int i=0;i<10;i++){
            amount_char_array[i]='\0';
        }

        for(int x=0; x<quantity_of_amount-1;x++){
            amount_char_array[x]=temp.trc[a].note[index_counter];
            index_counter++;
        }
        charArray_to_unsigned_fun(amount_char_array);

        unsigned int current_record_amount = charArray_to_unsignedInt_data;
//        printf("current_record_amount:%u\n",current_record_amount);


        for(int xx=index_counter;xx<current_record_counter;xx++){

            if(temp.trc[a].note[xx]=='!'){

                break;
            }
            index_counter++;

        }
        day_char_array[0]=temp.trc[a].note[index_counter+5];
        day_char_array[1]=temp.trc[a].note[index_counter+6];
        charArray_to_unsigned_fun(day_char_array);
//        printf("current day : %u\n",charArray_to_unsignedInt_data);



        if(charArray_to_unsignedInt_data != current_day_toTransfer){
            break;
        }
        total_amount_for_same_day+=current_record_amount;
        index_counter=0;
    }
    printf("Total amount for same day: %u",total_amount_for_same_day);
    return total_amount_for_same_day;

}
unsigned int calculate_amounts_same_days_for_withdrawal(){
    current_data_toTransfer();
    unsigned int total_amount_for_same_day = 0;
    int end=temp.noOfWithdrawalRecord;

    int index_counter = 0;
    char amount_char_array[10];
    char day_char_array[3];
    for(int a=end-1;a>=0;a--){
        int current_record_counter = charCounting(temp.trc[a].withdrawRecord);

        for(int aa=0;aa<current_record_counter;aa++){
            if(temp.trc[a].withdrawRecord[aa] == '$'){
                break;
            }
            index_counter++;
        }
        int quantity_of_amount = 0;
        for(int aaa=index_counter;aaa<current_record_counter;aaa++){
            if(temp.trc[a].withdrawRecord[aaa]=='-'){
                break;
            }
            quantity_of_amount++;
//            index_counter++;
        }
        index_counter++;
        for(int i=0;i<10;i++){
            amount_char_array[i]='\0';
        }

        for(int x=0; x<quantity_of_amount-1;x++){
            amount_char_array[x]=temp.trc[a].withdrawRecord[index_counter];
            index_counter++;
        }
        charArray_to_unsigned_fun(amount_char_array);

        unsigned int current_record_amount = charArray_to_unsignedInt_data;



        for(int xx=index_counter;xx<current_record_counter;xx++){

            if(temp.trc[a].withdrawRecord[xx]=='!'){

                break;
            }
            index_counter++;

        }
        day_char_array[0]=temp.trc[a].withdrawRecord[index_counter+5];
        day_char_array[1]=temp.trc[a].withdrawRecord[index_counter+6];
        charArray_to_unsigned_fun(day_char_array);




        if(charArray_to_unsignedInt_data != current_day_toTransfer){
            break;
        }
        total_amount_for_same_day+=current_record_amount;
        index_counter=0;
    }
    printf("Total amount for same day: %u",total_amount_for_same_day);
    return total_amount_for_same_day;

}
void get_limit_amount(){

    int acc_level = temp.acc_level;
    char pOrb = temp.pOrb[0];
    int p_or_b =0;
    if(pOrb == 'p'){
        p_or_b = 1;
    }else{
        p_or_b = 2;
    }

    switch (acc_level) {

        case 1:
            if(p_or_b == 1){
                trans_limit=100000;
            }else{
                trans_limit = 1000000;
            }
            break;
        case 2:
            if(p_or_b == 1){
                trans_limit = 50000;
            }else{
                trans_limit = 500000;
            }
            break;
        case 3:
            if(p_or_b == 1){
                trans_limit = 10000;
            }else{
                trans_limit = 100000;
            }
            break;
        default:
            break;
    }
}
void transfer_money(unsigned int amount){
    printf("loading to transfer.....\n");
    unsigned  int total_amount = calculate_amounts_same_days();
    printf("\nName:%s : You have transferred today: %u",temp.name,total_amount);

    get_limit_amount();


    if((total_amount+amount)>trans_limit){


        printf("\nIf you transfer $%u ,the amount you transfered today will be %u",amount,(total_amount+amount));
        printf("\nExceeded Limit Amount!\n");
        printf("So you can't tranfer!\n");
        printf("You can transfer amount for : %u\n",trans_limit-total_amount);
        userSector();

    }

    temp.cur_amount=temp.cur_amount-amount;
    receiverInfo.cur_amount=receiverInfo.cur_amount+amount;
    transaction_record('t',amount);
    transaction_record('r',amount);
    copy_struct_to_tree(db_root
                        ,temp);
    copy_struct_to_tree(db_root
                        ,receiverInfo);
    printf("Transaction succeed!");
    userSector();


}
void withdraw_money(){

    unsigned int to_withdraw=0;
    char withdraw_pass[50];
    printf("Name: %s\nCurrent Amount : %u\n",temp.name,temp.cur_amount);
    unsigned  int total_amount = calculate_amounts_same_days_for_withdrawal();
    printf("\nName:%s : You have withdrawed today: %u\n",temp.name,total_amount);


    printf("Enter your amount to withdraw:");
    scanf("%u",&to_withdraw);
    if(to_withdraw>=temp.cur_amount-1000){
        printf("Insufficient Amount to withdraw: %u\n",to_withdraw-(temp.cur_amount-1000));
        withdraw_money();
    }
    get_limit_amount();

    if((total_amount+to_withdraw)>trans_limit){

        printf("\nExceeded Limit Amount!\n");
        printf("You can only withdraw %u for today!\n",trans_limit-total_amount);
        userSector();

    }

    else{

        printf("Enter your password to proceed withdraw:");
        scanf(" %[^\n]",&withdraw_pass[0]);

        two_charArray=-1;
        compare_two_charArray(temp.password,withdraw_pass);

        if(two_charArray==-1){
            printf("Wrong credential: \n");
            withdraw_money();
        }else{
            int withdraw_option = 0;

            temp.cur_amount=temp.cur_amount-to_withdraw;
            printf("Withdraw successfully proceed:\n");
            transaction_record_for_withdrawal(to_withdraw);
            copy_struct_to_tree(db_root
                                ,temp);
            printf("Your current amount: %u\n",temp.cur_amount);

            printf("Press 1 to withdraw again:\nPress 2 to get to user sector:");
            scanf("%d",&withdraw_option);

            if(withdraw_option == 1){
                withdraw_money();
            }else if(withdraw_option == 2){

                userSector();

            }else{
                printf("Invalid Option!\n");
                userSector();
            }
        }

    }

}
void update_information() {

    int user_option = 0;
    char input[2];

    printf("\nYou can update your account information here!\n");
    printf("Press 1 to change your name:\nPress 2 to change your password:\nPress 3 to go back to user sector:");

    scanf(" %[^\n]",&input[0]);
    user_option = check_input(input);
    if(user_option == 49){
        char new_name[30];
        char up_password[50];
        printf("Enter your new name:");
        scanf(" %[^\n]",&new_name[0]);

        two_charArray = -1;
        while (two_charArray == -1){
            printf("Enter your password to proceed:");
            scanf(" %[^\n]",&up_password[0]);
            compare_two_charArray(up_password,temp.password);
            if(two_charArray == -1) {
                printf("Wrong password!Try again\n");

            }

        }

        copy_two_char_array(temp.name,new_name);
        update_information_record('N');
        copy_struct_to_tree(db_root
                            ,temp);
        printf("Your name is successfully updated!\n");
        printf("Your new name is %s",temp.name);

        update_information();



    }else if(user_option == 50){

        char new_pass[50];
        char old_pass[50];

        printf("Enter your new password:");
        scanf(" %[^\n]",&new_pass[0]);

        two_charArray = -1;
        while(two_charArray == -1){
            printf("Enter your old password:");
            scanf(" %[^\n]",&old_pass[0]);
            compare_two_charArray(old_pass,temp.password);
            if(two_charArray == -1){
                printf("Wrong password!Try again!\n");
            }
        }
        copy_two_char_array(temp.password,new_pass);
        update_information_record('P');
        copy_struct_to_tree(db_root ,temp);
        printf("Updating password successfully!\n");

        update_information();

    }else if(user_option == 51){
        userSector();
    }else{
        printf("Invalid option!\n");
        update_information();
    }

}
void cashIn() {
    printf("Welcome from CashIn Section!\n");
    unsigned int amount = 0;
    char cashInpass[50];
    printf("Enter your amount:");
    scanf("%u",&amount);

    two_charArray = -1;
    while(two_charArray == -1){
        printf("Enter your password to proceed:");
        scanf(" %[^\n]",&cashInpass[0]);
        compare_two_charArray(cashInpass,temp.password);
        if(two_charArray == -1){
            printf("Wrong password!Try again!\n");
        }
    }
    temp.cur_amount=temp.cur_amount+amount;
    printf("Cash In successfully\n");
    printf("Your amount is %u now!\n",temp.cur_amount);
    cashIn_record(amount);
    copy_struct_to_tree(db_root ,temp);
    userSector();

}
void view_history(){
    char input[2];
    printf("Press 1 to view your transfer records:\nPress 2 to view your withdraw records:\nPress 3 to view cash in records:\n"
           "Press 4 to view update records:\nPress 5 to go back to user_sector:");
    scanf(" %[^\n]",&input[0]);
    int user_option=check_input(input);

    if(user_option == 49){
        printf("\n\nYour transfer records:\n");
        printf("___________________________________________________\n");
        if(temp.noOfTransferRecord == 0){
            printf("You have no transfer records!\n");
        }else{
            for(int i=0;i<temp.noOfTransferRecord;i++){
                printf("%s\n", temp.trc[i].note);

            }
        }
        printf("___________________________________________________\n");
        view_history();

    }
    else if(user_option == 50){
        printf("\n\nYour withdraw records:\n");
        printf("___________________________________________________\n");
        if(temp.noOfWithdrawalRecord == 0){
            printf("You have no withdraw records!\n");
        }else{
            for(int i=0;i<temp.noOfWithdrawalRecord;i++){
                printf("%s\n", temp.trc[i].withdrawRecord);

            }
        }
        printf("___________________________________________________\n");
        view_history();


    }
    else if(user_option == 51){
        printf("\n\nYour cashIn records:\n");
        printf("___________________________________________________\n");
        if(temp.noOfCashInRecord == 0){
            printf("You have no cashIn records!\n");
        }else{
            for(int i=0;i<temp.noOfCashInRecord;i++){
                printf("%s\n", temp.trc[i].cashInRecord);

            }
        }
        printf("___________________________________________________\n");
        view_history();

    }
    else if(user_option == 52){
        printf("\n\nYour update records:\n");
        printf("___________________________________________________\n");
        if(temp.noOfUpdateRecord == 0){
            printf("You have no update records!\n");
        }else{
            for(int i=0;i<temp.noOfUpdateRecord;i++){
                printf("%s\n", temp.trc[i].updateRecord);

            }
        }
        printf("___________________________________________________\n");
        view_history();

    }
    else if(user_option == 53){
        userSector();
    }
    else{
        printf("Invalid Option!");
        view_history();
    }
}
void cashIn_record(unsigned int amount){
    int trc_index = temp.noOfCashInRecord;
    char cashIn_string[9] = {'-','c','a','s','h','i','n','-','$'};
    int index_point =0;
    integer_to_char(amount);
    int amount_count = charCounting(int_to_char_array_data);
    int name_count = charCounting(temp.name);
    for(int i=0;i<name_count;i++){
        temp.trc[trc_index].cashInRecord[index_point]=temp.name[i];
        index_point++;
    }
    for(int i=0;i<9;i++){
        temp.trc[trc_index].cashInRecord[index_point]=cashIn_string[i];
        index_point++;
    }
    for(int i=0;i<amount_count;i++){
        temp.trc[trc_index].cashInRecord[index_point]=int_to_char_array_data[i];
        index_point++;
    }
    getTime();
    for(int i=0;i<25;i++){
        temp.trc[trc_index].cashInRecord[index_point]=Ctime[0].c_time[i];
        index_point++;
    }
    temp.noOfCashInRecord++;

}
void copy_struct_to_tree(struct node* root ,struct data newInfo){

    if(root == NULL){
        return;
    }


    if(newInfo.id == root->info.id){
        root ->info = newInfo;
    }
    else if(newInfo.id < root ->info.id){
        copy_struct_to_tree(root ->left, newInfo);
    }
    else{
        copy_struct_to_tree(root ->right, newInfo);
    }


}
void transaction_record(char who,unsigned int amount){

    int trans_name_counter= charCounting(temp.name);
    int receiver_name_counter = charCounting(receiverInfo.name);
    integer_to_char(amount);
    int amount_count = charCounting(int_to_char_array_data);
    getTime();
//    int current_count= charCounting(current_time);


    char from[5]={'f','r','o','m','-'};
    char to[4]={'-','t','o','-'};
    char at[4]={'-','a','t','-'};

    if(who == 't'){
        int index_point=0;
        int trans_current_index = temp.noOfTransferRecord;
        for(int i=0;i<5;i++){
            temp.trc[trans_current_index].note[i]=from[i];
            index_point++;
        }
        for(int i=0;i<trans_name_counter;i++){
            temp.trc[trans_current_index].note[index_point]=temp.name[i];
            index_point++;
        }
        for(int i=0;i<4;i++){
            temp.trc[trans_current_index].note[index_point]=to[i];
            index_point++;
        }
        for(int i=0;i<receiver_name_counter;i++){
            temp.trc[trans_current_index].note[index_point]=receiverInfo.name[i];
            index_point++;
        }

        temp.trc[trans_current_index].note[index_point]='$';
        index_point++;

        for(int i=0;i<amount_count;i++){
            temp.trc[trans_current_index].note[index_point]=int_to_char_array_data[i];
            index_point++;
        }
        getTime();
        for(int i=0;i<25;i++){
            temp.trc[trans_current_index].note[index_point] = Ctime[0].c_time[i];
            index_point++;
        }


        temp.noOfTransferRecord++;
    }else{
        char rec[14]={'-','R','e','c','e','i','v','e','-','F',
                      'r','o','m','-'};



        int index_point=0;
        int rec_current_index = receiverInfo.noOfTransferRecord;
        for(int i=0;i<receiver_name_counter;i++){
            receiverInfo.trc[rec_current_index].note[i]=receiverInfo.name[i];
            index_point++;
        }
        for(int i=0;i<14;i++){
            receiverInfo.trc[rec_current_index].note[index_point]=rec[i];
            index_point++;
        }
        for(int i=0;i<trans_name_counter;i++){
            receiverInfo.trc[rec_current_index].note[index_point]=temp.name[i];
            index_point++;
        }
        receiverInfo.trc[rec_current_index].note[index_point]='$';
        index_point++;
        for(int i=0;i<amount_count;i++){
            receiverInfo.trc[rec_current_index].note[index_point]=int_to_char_array_data[i];
            index_point++;
        }
        for(int a=0;a<25;a++){
            receiverInfo.trc[rec_current_index].note[index_point]=Ctime[0].c_time[a];
            index_point++;
        }

        receiverInfo.noOfTransferRecord++;
    }

}
void transaction_record_for_withdrawal(unsigned int amount){

    int userName_counter= charCounting(temp.name);

    integer_to_char(amount);
    int amount_count = charCounting(int_to_char_array_data);
    int current_trans_index = temp.noOfWithdrawalRecord;
    getTime();
//    int current_count= charCounting(current_time);



    char withdraw[12]={'-','w','i','t','h','d','r','a','w','e','d','-'};


    int index_point=0;

    for(int i=0;i<userName_counter;i++){
        temp.trc[current_trans_index].withdrawRecord[index_point]=temp.name[i];
        index_point++;
    }
    for(int i=0;i<12;i++){
        temp.trc[current_trans_index].withdrawRecord[index_point]=withdraw[i];
        index_point++;
    }


    temp.trc[current_trans_index].withdrawRecord[index_point]='$';
    index_point++;

    for(int i=0;i<amount_count;i++){
        temp.trc[current_trans_index].withdrawRecord[index_point]=int_to_char_array_data[i];
        index_point++;
    }
    getTime();
    for(int i=0;i<25;i++){
        temp.trc[current_trans_index].withdrawRecord[index_point] = Ctime[0].c_time[i];
        index_point++;
    }


    temp.noOfWithdrawalRecord++;



}
void update_information_record(char type){
    int trc_index = temp.noOfUpdateRecord;
    if(type == 'N'){
        char update_String[25] = {'Y','o','u','-','c','h','a','n','g','e','d',
                                  '-','y','o','u','r','-','n','a','m','e','-','t',
                                  'o','-'}   ;
        int nameCount = charCounting(temp.name);
        int index_point=0;
        for(int i=0;i<25;i++){
            temp.trc[trc_index].updateRecord[index_point]=update_String[i];
            index_point++;
        }
        for(int i=0;i<nameCount;i++){
            temp.trc[trc_index].updateRecord[index_point]=temp.name[i];
            index_point++;
        }
        getTime();
        for(int i=0;i<25;i++){
            temp.trc[trc_index].updateRecord[index_point] = Ctime[0].c_time[i];
            index_point++;
        }
        temp.noOfUpdateRecord++;

    }
    else{
        char update_String[25]={'Y','o','u','-','c','h','a','n','g','e','d',
                                '-','y','o','u','r','-','p','a','s','s','w',
                                'o','r','d'};

        int index_point =0;


        for(int i=0;i<25;i++){
            temp.trc[trc_index].updateRecord[index_point]=update_String[i];
            index_point++;

        }
        getTime();
        for(int i=0;i<25;i++){
            temp.trc[trc_index].updateRecord[index_point] = Ctime[0].c_time[i];
            index_point++;
        }
        temp.noOfUpdateRecord++;

    }
}
void integer_to_char(unsigned int value){
    FILE *fptr= fopen("100.txt","w");
    if(fptr == NULL){
        printf("file opening error at integer_to_char:\n");
    }else{
        fprintf(fptr,"%u",value);
    }
    fclose(fptr);
    FILE *fptr2= fopen("100.txt","r");
    fscanf(fptr2,"%s",&int_to_char_array_data[0]);

}
void charArray_to_unsigned_fun(char charArray[]){
    FILE *fptr= fopen("100.txt","w");
    if(fptr == NULL){
        printf("file opening error at integer_to_char:\n");
    }else{
        fprintf(fptr,"%s",charArray);
    }
    fclose(fptr);
    FILE *fptr2= fopen("100.txt","r");
    fscanf(fptr2,"%u",&charArray_to_unsignedInt_data);
}
int check_input(char input[2]){
    if( input[0]>=49 &&input[0]<= 57 && input[1]=='\0'){
        return input[0];
    } else{
        return -1;
    }
}