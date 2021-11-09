# Classify-spam-comment
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

## Evaluation
~~~
make => ./trainer => gcc predictor.c -o p => ./p
~~~
* Through these results, it can be confirmed that the precision and recall change according to the thresh value of the trainer's vocabulary reduction.
* When the classification threshold is decreased, the precision value increases and the recall value decreases.
* When the classification threshold is increased, the precision value decreases and the recall value increases.
* It can be seen that the precision and recall values conflict with each other.
* Therefore, it can be seen that the performance varies depending on how the threshold of the classifier is determined.

## Limitation
1. If the value of the newly given feature type does not exist in the previously learned feature, the probability is 0, and multiplying it will result in a final probability of 0. So, I use Laplace smoothing for all probability.
2. Since the probability derived using the classifier is less than 1, if there is a lot of probability to multiply, the value continues down, and the value comes out so small that it is difficult to distinguish. So, by taking logs on all the probabilities, I prevented underflow.
----
If you have any questions, don't hesitate to send e-mail swy12190@gmail.com
 
