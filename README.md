# Classify-twitter-spam-comment
Distinguish spam messages by using Naive Bayes Classifiers (Discrete Mathmatics)
## Description
Check whether the string input is negative or not by using the machine-learning data.

(1) using the given dataset to create a trainer to make prediction model that is a large table format. 
(2) using prediction model to evaluate whether a given string is negative or non-negative.
## Approach
### 1. Implement trainer module(trainer.c)
 1. tokenization
 2. Normalization
 3. Stopword removal
 4. Vocaburarly reduction
 5. Construct prediction model

### 2. Implement predictor module(predictor.c)
 1. Enter the file name
 2. Text is entered line by line and stored in a "string" file. 
 3. Tokenization by using “string” file (s_token.txt)
 4. Normalization by using “s_token.txt” file (s_norm.txt)
 5. Remove stop word by using “s_norm.txt”(s_stop.txt)
 6. In “s_stop.txt” file, bring all the words into the array.
 7. Use the functions below to find negative, non-negative probabilities by word in the prdiction model.
 8. Log scaling
 9. Store result (result.txt)

### 3. Evaluation
'''c
make => ./trainer => gcc predictor.c -o p => ./p
'''
 
