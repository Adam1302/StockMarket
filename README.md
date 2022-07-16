How the observer pattern works:
    Publish-Subscribe Mode:
        - 1 Class: Publisher/Subject - data is simulated
        - 1+ Class(es): Subscriber/Observer - react to data
    
    Sequence:
        1. Subject's data is updated
        2. Subject's notifyObservers method is called
        3. Each observer within the vector calls the getState method of the subject to get the state and react accordingly
            - Each observer, thus, must have a pointer or reference to the subject they watch