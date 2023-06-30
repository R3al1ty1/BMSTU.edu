import {ProductComponent} from "../../components/product/index.js";
import {BackButtonComponent} from "../../components/back-button/index.js";
import {MainPage} from "../main/index.js";

export class ProductPage {
    constructor(parent, id) {
        this.parent = parent
        this.id = id
    }

    getData() {
        return [[{
            id: 1,
            src: "https://img2.akspic.ru/crops/6/1/5/2/72516/72516-erg-liniya-dyuna-pustynya-eolovogo_relefa-1920x1080.jpg",
            title: `Пустынные равнины`,
            text: "Оцените картинку"
        },
        {
            id: 1,
            src: "https://img2.akspic.ru/crops/6/6/1/0/7/170166/170166-dubaj-pustynya-safari-makaron-dubajskaya_pustynya-1920x1080.jpg",
            title: `Сафари`,
            text: "Оцените картинку"
        },
        {
            id: 1,
            src: "https://s1.1zoom.ru/b5050/261/427744-sepik_1920x1080.jpg",
            title: `Дюны`,
            text: "Оцените картинку"
        }],
        [{
            id: 2,
            src: "https://www.nastol.com.ua/pic/202102/1920x1080/nastol.com.ua-448036.jpg",
            title: `Озеро на закате`,
            text: "Оцените картинку"
        },
        {
            id: 2,
            src: "https://s1.1zoom.ru/b5050/296/Mountains_Scenery_Sky_452695_1920x1080.jpg",
            title: `Горный ландшафт`,
            text: "Оцените картинку"
        },
        {
            id: 2,
            src: "https://images.wallpaperscraft.ru/image/single/gory_ozero_pejzazh_132141_1920x1080.jpg",
            title: `Снежный пейзаж`,
            text: "Оцените картинку"
        }],
        [{
            id: 3,
            src: "https://s1.1zoom.ru/b2350/859/Waterfalls_Moss_513909_1920x1080.jpg",
            title: `Тропический водопад`,
            text: "Оцените картинку"
        },
        {
            id: 3,
            src: "https://wpapers.ru/wallpapers/nature/Waterfalls/7358/1920x1080_Солнечный-водопад.jpg",
            title: `Лесной водопад`,
            text: "Оцените картинку"
        },
        {
            id: 3,
            src: "https://img1.akspic.ru/crops/0/4/7/8/2/128740/128740-niagarskij_vodopad-rastitelnost-vodoem-prirodnyj_landshaft-vodopad-1920x1080.jpg",
            title: `Ниагарский водопад`,
            text: "Оцените картинку"
        }]
    ]
    }

    get pageRoot() {
        return document.getElementById('product-page')
    }

    getHTML() {
        return (
            `
                <div id="product-page"></div>
            `
        )
    }

    clickBack() {
        const mainPage = new MainPage(this.parent)
        mainPage.render()
    }
    
    render() {
        this.parent.innerHTML = ''
        const html = this.getHTML()
        this.parent.insertAdjacentHTML('beforeend', html)
    
        const backButton = new BackButtonComponent(this.pageRoot)
        backButton.render(this.clickBack.bind(this))
    
        const data = this.getData()
        data.forEach((item) => {
            item.forEach((thing) => {
                if(thing.id == this.id) {
                    const stock = new ProductComponent(this.pageRoot)
                    stock.render(thing,data)
                }
            })
        }
        )
    }
}