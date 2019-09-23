import bayes

def main():
    # the number of words in the dictionary
    word_num = 2500
    # file that contains features of emails to be used in training
    train_feature_filename = "./data/train-features.txt"
    # file that contains labels of emails to be used in training
    train_label_filename = "./data/train-labels.txt"
    # the number of training emails
    train_email_num = 700
    # file that contains features of emails to be used in testing
    test_feature_filename = "./data/test-features.txt"
    # file that contains labels of emails to be used in testing
    test_label_filename = "./data/test-labels.txt"
    # the number of testing emails
    test_email_num = 260
    # train naive bayes model
    model = bayes.train(train_feature_filename, train_label_filename, train_email_num, word_num)
    # make predictions on test data
    bayes.test(model, test_feature_filename, test_label_filename, test_email_num, word_num)

if __name__ == "__main__":
    main()