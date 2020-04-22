#include <iostream>
#include <fstream>  // file operation

#include <chrono>   // getting
#include <unistd.h> // elapsed time

#include "HashTable.h"
#include "Person.h"
#include "LinkedList.h"

// including for template defination linkage
#include "LinkedList.cpp"
#include "Node.cpp"

/*------------------------------------------------------------------------------*/
#include "Log.h"

#undef LOG_LEVEL
#ifndef LOG_LEVEL_CONF_TEST
#define LOG_LEVEL LOG_LEVEL_INFO
#else /* LOG_LEVEL_CONF_TEST */
#define LOG_LEVEL LOG_LEVEL_CONF_TEST
#endif /* LOG_LEVEL_CONF_TEST */

/*------------------------------------------------------------------------------*/
#define TEST_ITERATION_COUNT 1000

/*------------------------------------------------------------------------------*/
static LinkedList<Person>* readPersonFromFile(const char *fileName);
static void tableSearchAndLog(HashTable *hashTable, string str, \
                                              bool logging = false);
static void listSearchAndLog(LinkedList<Person> *list, string str, \
                                                bool logging = false);

/*------------------------------------------------------------------------------*/
int 
main(int argc, char *argv[]){
  string defaultFileName = "Data/persons";
  const char *fileName = (argc > 1) ? argv[1] : defaultFileName.c_str();
  
/*------------------------------------------------------------------------------*/
  LOG_INFO("Step-1: Reading person info from file %s\n", fileName);
  LinkedList<Person> *personList = readPersonFromFile(fileName);
  if(personList == NULL || personList->getItemCount() == 0){
    LOG_ERR("PersonList is empty breaking!\n");
    return -1;
  }

/*------------------------------------------------------------------------------*/
  int itemCount = personList->getItemCount();
  LOG_INFO("Step-2: %d person data loaded, inserting hashTable!\n", itemCount);

  /* init hashTable with current item size and collision uplimit
   * if performance not enough for you decrease collision uplimit
   * if you need more memory increase collision uplimit 
   *
   * WARN: if remapping too long increase collision uplimit again 
   * TIP: you may want to start hashTable size with doubling itemCount when
   *      copiling with Quadratic Probing */
  HashTable *hashTable = new HashTable(itemCount, 50);

  Node<Person> *personNode = personList->get(0);
  while(personNode != NULL){
    Person person = personNode->val();

    hashTable->insert(person.key(), (void *)personNode);
    personNode = personNode->next;
  }
  LOG_INFO("Step-2: all person inserted to hashTable, table size = %d!\n", \
    hashTable->getTableSize());

/*------------------------------------------------------------------------------*/
  LOG_INFO("Step-3: Getting test emails!\n");
  /* LinkedList->get(index) returns Node<Person> -> Person
   * Node<Person>->val()    returns Person
   * Person.getEmail()      returns email */
  string headEmail = personList->get(0)->val().getEmail();
  string middleEmail = personList->get(personList->getItemCount() / 2)->val().getEmail();
  string lastEmail = personList->get(personList->getItemCount() - 1)->val().getEmail();
  LOG_INFO("Step-3: EmailSet: [%s][%s][%s]\n", headEmail.c_str(), \
    middleEmail.c_str(), lastEmail.c_str());

/*------------------------------------------------------------------------------*/
  LOG_INFO("Step-4: Testing hashTable search performance!\n");

  LOG_INFO("Step-4: hashTable search performances in nanoseconds: ");
  // seaching head
  auto start = chrono::high_resolution_clock::now();
  for(int i = 0; i < TEST_ITERATION_COUNT; i++){
    tableSearchAndLog(hashTable, headEmail);
  }
  auto elapsed = chrono::high_resolution_clock::now() - start;
  long long nanoseconds = chrono::duration_cast<chrono::nanoseconds>(elapsed).count();
  LOG_INFO_("[%llu]", nanoseconds / TEST_ITERATION_COUNT);

  // seaching middle
  start = chrono::high_resolution_clock::now();
  for(int i = 0; i < TEST_ITERATION_COUNT; i++){
    tableSearchAndLog(hashTable, middleEmail);
  }
  elapsed = chrono::high_resolution_clock::now() - start;
  nanoseconds = chrono::duration_cast<chrono::nanoseconds>(elapsed).count();
  LOG_INFO_("[%llu]", nanoseconds / TEST_ITERATION_COUNT);

  // seaching last
  start = chrono::high_resolution_clock::now();
  for(int i = 0; i < TEST_ITERATION_COUNT; i++){
    tableSearchAndLog(hashTable, lastEmail);
  }
  elapsed = chrono::high_resolution_clock::now() - start;
  nanoseconds = chrono::duration_cast<chrono::nanoseconds>(elapsed).count();
  LOG_INFO_("[%llu]!\n", nanoseconds / TEST_ITERATION_COUNT);

/*------------------------------------------------------------------------------*/
  LOG_INFO("Step-5: Testing linkedList search performance!\n");

  LOG_INFO("Step-5: linkedList search performances in nanoseconds: ");
  // searching head
  start = chrono::high_resolution_clock::now();
  for(int i = 0; i < TEST_ITERATION_COUNT; i++){
    listSearchAndLog(personList, headEmail);
  }
  elapsed = chrono::high_resolution_clock::now() - start;
  nanoseconds = chrono::duration_cast<chrono::nanoseconds>(elapsed).count();
  LOG_INFO_("[%llu]", nanoseconds / TEST_ITERATION_COUNT);

  // seaching middle
  start = chrono::high_resolution_clock::now();
  for(int i = 0; i < TEST_ITERATION_COUNT; i++){
    listSearchAndLog(personList, middleEmail);
  }
  elapsed = chrono::high_resolution_clock::now() - start;
  nanoseconds = chrono::duration_cast<chrono::nanoseconds>(elapsed).count();
  LOG_INFO_("[%llu]", nanoseconds / TEST_ITERATION_COUNT);

  // seaching last
  start = chrono::high_resolution_clock::now();
  for(int i = 0; i < TEST_ITERATION_COUNT; i++){
    listSearchAndLog(personList, lastEmail);
  }
  elapsed = chrono::high_resolution_clock::now() - start;
  nanoseconds = chrono::duration_cast<chrono::nanoseconds>(elapsed).count();
  LOG_INFO_("[%llu]!\n", nanoseconds / TEST_ITERATION_COUNT);

/*------------------------------------------------------------------------------*/
  // clean up
  if(personList != NULL) delete personList;
  if(hashTable != NULL) delete hashTable;
  
  return 0;
}

/*------------------------------------------------------------------------------*/
static string
readNextWord(string& input, char parser){
  string word;
  bool passingOver = false;
  bool wordReading = true;

  int wordStartPoint = 0;
  unsigned int len = input.length();

  for(unsigned int i = 0; i < len; i++){
    if(i == len - 1){
      word = input.substr(wordStartPoint, len);
      input = "";
      return word;
    } else{
      if(input[i] == '"'){
        if(passingOver){
          // set word and input
          word = input.substr(wordStartPoint, i - 1);
          input = input.substr(i + 2, len);

          // set word reading done
          wordReading = false;
        } else{
          // set start point
          wordStartPoint = (i + 1);
        }
        // convert flag
        passingOver = !passingOver;
      } else if(!passingOver){
        if(input[i] == parser){
          if(wordReading){
            // set word and input
            word = input.substr(wordStartPoint, i);
            input = input.substr(i + 1, len);
          } else{
            // set start point
            wordStartPoint = (i + 1);
          }
        
          // convert flag
          wordReading = !wordReading;
        }
      }

      // check word reading done
      if(!wordReading){
        return word;
      }
    }
  }

  // return empty string on failure
  return "";
}

/*------------------------------------------------------------------------------*/
static LinkedList<Person>* 
readPersonFromFile(const char *fileName){
  LinkedList<Person> *list = new LinkedList<Person>();
  
  ifstream infile(fileName);

  string line;
  while(std::getline(infile, line, '\n')){
    // parse line to variables
    string firstName = readNextWord(line, ',');
    string lastName = readNextWord(line, ',');
    string companyName = readNextWord(line, ',');
    string address = readNextWord(line, ',');
    string city = readNextWord(line, ',');
    string county = readNextWord(line, ',');
    string postal = readNextWord(line, ',');
    string phone1 = readNextWord(line, ',');
    string phone2 = readNextWord(line, ',');
    string email = readNextWord(line, ',');
    string web = readNextWord(line, ',');

    // create and insert person to list
    Person person(email, lastName, companyName, address, city, county, \
      postal, phone1, phone2, firstName, web);
    list->insert(person);
  }

  infile.close();

  return list;
}

/*------------------------------------------------------------------------------*/
static void
tableSearchAndLog(HashTable *hashTable, string email, bool logging){
  // create personwith requested email
  Person emailPerson(email);
  // find from hashTable
  void *ptr = hashTable->search(emailPerson.key());

  if(ptr != NULL){
    Node<Person>* personNode = (Node<Person> *)ptr;
    Person person = personNode->val();
    if(logging){
      person.print();
    }
  }
}

/*------------------------------------------------------------------------------*/
static void
listSearchAndLog(LinkedList<Person> *list, string email, bool logging){
  // create personwith requested email
  Person person(email);
  // Person class == operator checks only email
  Node<Person>* personNode = list->search(person);

  if(personNode != NULL){
    Person person = personNode->val();
    if(logging){
      person.print();
    }
  }
}
