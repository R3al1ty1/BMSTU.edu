//import {ButtonComponent} from "../../components/button/index.js";
import {ProductCardComponent} from "../../components/product-card/index.js";
import {ProductPage} from "../product/index.js";
let arr = [0,0,0]
export class MainPage {
    constructor(parent) {
        this.parent = parent;
    }
    getData() {
        return [
            {
                id: 1,
                src: "https://images.wallpaperscraft.ru/image/single/pustynia_pesok_diuny_150124_1920x1080.jpg",
                title: "Пустыни, число переходов:",
                text: arr[0]
               
            },
            {
                id: 2,
                src: "https://img2.akspic.ru/crops/0/6/4/7460/7460-kraternoe_ozero-pejzazhi_gor-voda-rassvet-pejzazhi-1920x1080.jpg",
                title: "Пейзажи, число переходов:",
                text: arr[1]
            },
            {
                id: 3,
                src: "https://img1.akspic.ru/crops/7/2/9/1/0/101927/101927-verhnij_vodopad_jelloustoun-nacionalnyj_park_grand_kanon-musoroprovod-otkos-nacionalnyj_park_denali_i_zapovedn-1920x1080.jpg",
                title: "Водопады, число переходов:",
                text: arr[2]
            }
        ]
    }
    
    get pageRoot() {
        return document.getElementById('main-page')
    }
        
    getHTML() {
        return (
            `
                <div id="main-page" class="d-flex flex-wrap"><div/>
            `
        )
    }
    
    clickCard(e) {
        const cardId = e.target.dataset.id
        
        const productPage = new ProductPage(this.parent, cardId)
        arr[cardId-1] += 1
        console.log(arr)
        productPage.render()
    }
    

render() {
    this.parent.innerHTML = ''
    const html = this.getHTML()
    this.parent.insertAdjacentHTML('beforeend', html)
    
    const data = this.getData()
    data.forEach((item) => {
        const productCard = new ProductCardComponent(this.pageRoot)
        productCard.render(item, this.clickCard.bind(this))
    })
}

}