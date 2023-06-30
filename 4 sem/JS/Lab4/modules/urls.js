import {accessToken, serviceToken, appKey, tempToken, version} from "./consts.js";

class Urls {
    constructor() {
        this.url = 'https://api.vk.com/method'
        this.commonInfo = `access_token=${accessToken}&v=${version}`
        this.uncommonInfo = `access_token=${serviceToken}&v=${version}`
        this.persInfo = `access_token=${appKey}&v=${version}`
        this.statusInfo = `access_token=${tempToken}&v=${version}`
    }

    getUserInfo(userId) {
        return `${this.url}/users.get?user_id=${userId}&fields=photo_400_orig&${this.commonInfo}`
    }
    getGroupMembers(groupId) {
        return `${this.url}/groups.getMembers?group_id=${groupId}&fields=photo_400_orig&${this.commonInfo}&sort=time_asc`
    }
    oAuth(appId, redirectUri) {
        return `https://oauth.vk.com/authorize?client_id=${appId}&redirect_uri=${redirectUri}&response_type=token&scope=wall&${this.commonInfo}`
    }
    setStatus(statusText) {
        return `${this.url}/status.set?text=${statusText}&${this.statusInfo}`
    }
}
export const urls = new Urls()