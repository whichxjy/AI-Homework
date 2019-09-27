from collections import namedtuple
from math import log10

# Naive Bayes Model
Model = namedtuple('Model', ['prob_spam', 'prob_word_spam', 'prob_word_ham'])

# Spam Label
SPAM = 1
# Ham Label
HAM = 0

def train(train_feature_filename, train_label_filename, train_email_num, word_num):
    """Train the model"""
    # load the features into a full matrix (email_id | word_id | occurrence)
    train_matrix = load_feature(train_feature_filename, train_email_num, word_num)
    # load the labels into a list (email_id => label)
    train_labels = load_labels(train_label_filename)
    # filter email ids with labels
    spam_email_ids = []
    ham_email_ids = []
    for i in range(train_email_num):
        if train_labels[i] == SPAM:
            spam_email_ids.append(i)
        else:
            ham_email_ids.append(i)
    # P(spam)
    # = number-of-spam / number-of-email
    prob_spam = len(spam_email_ids) / train_email_num
    # P(word[i] | spam)
    # = (number-of-word[i]-in-spam + 1) / (number-of-words-in-spam + number-of-words)
    spam_word_count = [0 for i in range(word_num)]
    spam_word_num = 0
    for spam_email_id in spam_email_ids:
        spam_word_occurs = train_matrix[spam_email_id]
        for word_id, word_occur in enumerate(spam_word_occurs):
            spam_word_count[word_id] += word_occur
            spam_word_num += word_occur
    prob_word_spam = []
    for word_id in range(word_num):
        prob_word_spam.append((spam_word_count[word_id] + 1) / (spam_word_num + word_num))
    # P(word[i] | ham)
    # = (number-of-word[i]-in-ham + 1) / (number-of-words-in-ham + number-of-words)
    ham_word_count = [0 for i in range(word_num)]
    ham_word_num = 0
    for ham_email_id in ham_email_ids:
        ham_word_occurs = train_matrix[ham_email_id]
        for word_id, word_occur in enumerate(ham_word_occurs):
            ham_word_count[word_id] += word_occur
            ham_word_num += word_occur
    prob_word_ham = []
    for word_id in range(word_num):
        prob_word_ham.append((ham_word_count[word_id] + 1) / (ham_word_num + word_num))
    # return model
    return Model(prob_spam, prob_word_spam, prob_word_ham)

def test(model, test_feature_filename, test_label_filename, test_email_num, test_word_num):
    """Make predictions on test data"""
    # load the features into a full matrix (email_id | word_id | occurrence)
    test_matrix = load_feature(test_feature_filename, test_email_num, test_word_num)
    # load the labels into a list (email_id => label)
    test_labels = load_labels(test_label_filename)
    # predict each email in test data
    true_spam = 0
    false_spam = 0
    true_ham = 0
    false_ham = 0
    for email_id in range(test_email_num):
        word_occurs = test_matrix[email_id]
        predict_result = predict(model, word_occurs)
        if predict_result == SPAM and test_labels[email_id] == SPAM:
            true_spam += 1
        elif predict_result == SPAM and test_labels[email_id] == HAM:
            false_spam += 1
        elif predict_result == HAM and test_labels[email_id] == HAM:
            true_ham += 1
        else:
            false_ham += 1
    accuracy_score = (true_spam + true_ham) / test_email_num
    precision_score = true_spam / (true_spam + false_spam)
    recall_score = true_spam / (true_spam + false_ham)
    f1_score = (2 * precision_score * recall_score) / (precision_score + recall_score)
    # print result
    print("Accuracy score: " + str(accuracy_score))
    print("Precision score: " + str(precision_score))
    print("Recall score: " + str(recall_score))
    print("F1 score: " + str(f1_score))

def predict(model, word_occurs):
    """Predict whether an email is spam or not"""
    # ids of words that appear in this email
    appear_word_ids = [word_id for word_id, word_occur in enumerate(word_occurs) if word_occur > 0]
    # P(spam | appear-words) => spam?
    # math: P(spam) * P(appear-word[0] | spam) * P(appear-word[1] | spam) * ... * P(appear-word[n] | spam)
    # calculate: log(P(spam)) + log(P(appear-word[0] | spam)) + ... + log(P(appear-word[n] | spam))
    spam_score = log10(model.prob_spam)
    for appear_word_id in appear_word_ids:
        spam_score += log10(model.prob_word_spam[appear_word_id])
    # P(ham | appear-words) => ham?
    # math: P(ham) * P(appear-word[0] | ham) * P(appear-word[1] | ham) * ... * P(appear-word[n] | ham)
    # calculate: log(P(ham)) + log(P(appear-word[0] | ham)) + ... + log(P(appear-word[n] | ham))
    ham_score = log10(1 - model.prob_spam)
    for appear_word_id in appear_word_ids:
        ham_score += log10(model.prob_word_ham[appear_word_id])
    # Compare the two scores and make a decision about whether this email is spam
    if spam_score > ham_score:
        return SPAM
    else:
        return HAM

def load_feature(feature_filename, email_num, word_num):
    """Load the features into a full matrix"""
    matrix = [[0 for i in range(word_num)] for j in range(email_num)]
    with open(feature_filename, 'r', encoding='utf-8') as fp:
        for line in fp:
            # email_id | word_id | occurrence
            line_data = line.split()
            email_id = int(line_data[0]) - 1
            word_id = int(line_data[1]) - 1
            occur = int(line_data[2])
            matrix[email_id][word_id] += occur
    return matrix

def load_labels(label_filename):
    """Load the labels into a list (email_id => label)"""
    labels = []
    with open(label_filename, 'r', encoding='utf-8') as fp:
        for line in fp:
            labels.append(int(line))
    return labels