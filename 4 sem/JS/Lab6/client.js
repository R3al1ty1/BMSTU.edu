const getCard = async (id) => {
    let url = 'http://localhost:8000/stocks/' + id;
    console.log(url);
    try {
        let response = await fetch(url, {
            method: 'GET'
        });

        if (response.ok) {
            console.log(response)
            let result = await response.json();
            console.log(result);
        } else {
            console.log(response.status)
        }
    
        
    }
    catch (e) {
        console.log(e);
    }
    
}

getCard(2);